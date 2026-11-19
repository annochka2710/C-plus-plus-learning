#include <chrono>
#include <functional>
#include <iostream>
#include <numeric>
#include <stop_token>
#include <thread>
#include <vector>

void sum_values(const std::vector<int>& values, int& result) {
    result = std::accumulate(values.begin(), values.end(), 0);
}

void wait_for_stop(std::stop_token token, bool& observed) {
    while (!token.stop_requested()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    observed = true;
}

int main() {
    const std::vector<int> values{1, 2, 3, 4};
    int sum = 0;
    std::jthread calculator(sum_values, std::cref(values), std::ref(sum));
    calculator.join();
    std::cout << "Sum after join: " << sum << '\n';

    bool explicit_stop_observed = false;
    std::jthread worker(wait_for_stop, std::ref(explicit_stop_observed));
    // Токен передаёт jthread. Запрос допустим даже до входа в рабочую функцию.
    const bool first_request = worker.request_stop();
    const bool second_request = worker.request_stop();
    worker.join();
    std::cout << std::boolalpha
              << "First request: " << first_request << '\n'
              << "Second request: " << second_request << '\n'
              << "Explicit stop observed: " << explicit_stop_observed << '\n';

    bool automatic_stop_observed = false;
    {
        std::jthread scoped_worker(wait_for_stop,
                                  std::ref(automatic_stop_observed));
        // Деструктор отправит запрос остановки и дождётся завершения.
    }
    std::cout << "Destructor stop observed: " << automatic_stop_observed << '\n';

    return sum == 10 && first_request && !second_request
        && explicit_stop_observed && automatic_stop_observed ? 0 : 1;
}

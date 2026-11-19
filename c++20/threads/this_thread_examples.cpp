#include <chrono>
#include <iostream>
#include <thread>

int main() {
    const std::thread::id main_id = std::this_thread::get_id();
    std::thread::id worker_id;
    long long elapsed_ms = 0;

    std::thread worker([&worker_id, &elapsed_ms] {
        worker_id = std::this_thread::get_id();
        const auto start = std::chrono::steady_clock::now();
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
        const auto deadline = std::chrono::steady_clock::now()
                            + std::chrono::milliseconds(5);
        std::this_thread::sleep_until(deadline);
        std::this_thread::yield();
        elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::steady_clock::now() - start).count();
    });

    // Сохраняем ID до join: после join объект уже не связан с потоком.
    const std::thread::id object_id = worker.get_id();
    worker.join();

    std::cout << std::boolalpha
              << "Main ID: " << main_id << '\n'
              << "Worker ID: " << worker_id << '\n'
              << "Worker IDs match: " << (object_id == worker_id) << '\n'
              << "Main and worker differ: " << (main_id != worker_id) << '\n'
              << "Elapsed milliseconds (varies): " << elapsed_ms << '\n';

    return object_id == worker_id && main_id != worker_id ? 0 : 1;
}

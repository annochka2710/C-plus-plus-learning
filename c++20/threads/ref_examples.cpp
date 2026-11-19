#include <functional>
#include <iostream>
#include <thread>

void increment(int& value) {
    ++value;
}

void double_value(const int& value, int& result) {
    result = value * 2;
}

int main() {
    int value = 10;
    auto copy = value;
    ++copy;
    std::cout << "Copy: " << copy << ", original: " << value << '\n';

    auto reference = std::ref(value);
    auto another = reference;
    another.get() += 5;
    std::cout << "After reference_wrapper copy: " << value << '\n';

    std::thread writer(increment, std::ref(value));
    // Не обращаемся к value, пока writer может его менять.
    writer.join();
    std::cout << "After thread increment: " << value << '\n';

    int result = 0;
    std::thread reader(double_value, std::cref(value), std::ref(result));
    reader.join();
    std::cout << "Read via cref, doubled: " << result << '\n';

    return value == 16 && result == 32 ? 0 : 1;
}

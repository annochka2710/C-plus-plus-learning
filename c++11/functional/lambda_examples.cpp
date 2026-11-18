#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    auto square = [](int value) { return value * value; };
    std::cout << "square: " << square(4) << '\n';

    int offset = 10;
    auto snapshot = [offset](int value) { return value + offset; };
    auto live = [&offset](int value) { return value + offset; };
    offset = 20;
    std::cout << "copy/reference: " << snapshot(1) << ' ' << live(1) << '\n';

    int count = 0;
    auto next = [count]() mutable { return ++count; };
    auto independent = next;
    std::cout << "mutable: " << next() << ' ' << next() << ' '
              << independent() << "; original: " << count << '\n';

    std::vector<int> values{3, 1, 4, 2};
    std::sort(values.begin(), values.end(),
              [](int left, int right) { return left > right; });
    std::cout << "sorted:";
    for (int value : values) {
        std::cout << ' ' << value;
    }
    const int threshold = 2;
    const auto above = std::count_if(values.begin(), values.end(),
        [threshold](int value) { return value > threshold; });
    std::cout << "\nabove threshold: " << above << '\n';

    int (*function_pointer)(int) = [](int value) { return value + 1; };
    std::cout << "function pointer: " << function_pointer(4) << '\n';
}

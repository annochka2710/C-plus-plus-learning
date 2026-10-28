#include <iostream>
#include <stdexcept>

// факториал натурального чила n (n!) - произведение всех натуральных
// чисел от 1 до n включительно
//
// 0! = 1, 1! = 1
// 3! = 1 ⋅ 2 ⋅ 3 = 6
// 5! = 1 ⋅ 2 ⋅ 3 ⋅ 4 ⋅ 5 = 120

void checkInput(int n) {
    if (n < 0 || n > 20) {
        throw std::out_of_range("from 0 to 20");
    }
}

unsigned long long factorialLoop(int n) {
    unsigned long long result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}

unsigned long long factorialRecursion(const unsigned long long n) {
    checkInput(n);
    return (n == 0 || n == 1) ? 1 : (n * factorialRecursion(n - 1));
}

// constexpr
unsigned long long factorialRecursion2(unsigned long long n) {
    checkInput(n);
    if (n <= 1) {
        return 1;
    }
    return n * factorialRecursion(n - 1);
}

// факториал на этапе компиляции через рекурсию шаблонов
template <unsigned N> struct Factorial {
    static_assert(N <= 20, "till 20");
    static constexpr unsigned long long value = N * Factorial<N - 1>::value;
};
// специализация шаблона
template <> struct Factorial<0> {
    static constexpr unsigned long long value = 1;
};
// N - параметр шаблона, а не аргумент функции
// constexpr - значение переменной известно на этапе компиляции программы
template <unsigned N>
constexpr unsigned long long factorialTemplate() {
    return Factorial<N>::value;
}

int main() {
    // 
    static_assert(Factorial<5>::value == 120);
    static_assert(Factorial<20>::value == 2432902008176640000ULL);
    try {
        factorialRecursion(-1);
    } catch (const std::out_of_range& e) {
        std::cout << "error: " << e.what() << '\n';
    }
    return 0;
}
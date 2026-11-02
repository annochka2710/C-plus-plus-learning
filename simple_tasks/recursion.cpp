#include <iostream>

// Для 0! и 1! функция возвращает 1 автоматически:
// при n = 0 цикл не выполняется, а при n = 1 умножаем 1 на 1.
unsigned long long factorial(int n) {
    unsigned long long result = 1;

    for (int i = 1; i <= n; i++) {
        result *= i;
    }

    return result;
}

int main() {
    int n;
    std::cin >> n;

    if (n < 0) {
        std::cout << "Нет факториала отрицательного числа";
    }
    else {
        std::cout << n << "! = " << factorial(n) << std::endl;
    }

    return 0;
}
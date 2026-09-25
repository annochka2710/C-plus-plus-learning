#include <array>
#include <iostream>

// приём метапрограммирования: 
// таблица диспетчеризации (jump table) генерируется автоматически и не пишется руками.
// Например, можно вызывать TABLE[n](), где n известен только во время работы программы,
// и попадать в нужную шаблонную функцию func<n>.

// на этапе компиляции строим таблицу из 10 указателей на функции 
// func<0>...func<9>
// затем вызывает их по очереди из main

constexpr int TABLE_SIZE = 10;

template<int N>
int func() {
    return N;
}

//указатель на функцию без параметров, кот возвращает int
using func_t = int(*)();

// рекурсивный шаблон Helper
template <int Index, func_t... D>
struct Helper : Helper<Index + 1, D..., func<Index>> { };

// остановка рекурсии
template <func_t... D>
struct Helper<TABLE_SIZE, D...> {
    static constexpr std::array<func_t, TABLE_SIZE> TABLE = { D... };
};

// получение таблицы
constexpr std::array<func_t, TABLE_SIZE> TABLE = Helper<0>::TABLE;

int main() {
    // Использование таблицы
    for (func_t i : TABLE) {
        std::cout << i() << " ";
    }
    std::cout << std::endl;
    return 0;
}

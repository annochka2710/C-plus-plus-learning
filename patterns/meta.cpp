#include <array>
#include <iostream>

constexpr int TABLE_SIZE = 10;

template <int N> int func(void) {
    return N;
}

using func_t = int (*)(void);

// Вспомогательная структура для рекурсивной генерации
template <int Index, func_t... D> struct Helper : Helper<Index + 1, D..., func<Index>> {};

// Специализация для завершения рекурсии
template <func_t... D> struct Helper<TABLE_SIZE, D...> {
    static constexpr std::array<func_t, TABLE_SIZE> TABLE = {D...};
};

// Инициализация таблицы
constexpr std::array<func_t, TABLE_SIZE> TABLE = Helper<0>::TABLE;

int main() {
    // Использование таблицы
    for (func_t i : TABLE) {
        std::cout << i() << " ";
    }
    std::cout << std::endl;
    return 0;
}

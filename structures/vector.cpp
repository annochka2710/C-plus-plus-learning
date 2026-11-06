#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

void print(const std::vector<int>& values) {
    for (int value : values) {
        std::cout << value << ' ';
    }
    std::cout << '\n';
}

int main() {
    std::vector<int> values{10, 20, 30, 40};
    std::cout << "Исходный vector: ";
    print(values);

    // Доступ по индексу — O(1). Индексация начинается с 0.
    // operator[] не проверяет границы; at() проверяет и может бросить исключение.
    std::cout << "Элемент с индексом 2: " << values[2] << '\n';

    // reserve() выделяет место минимум для 8 элементов, но не меняет size().
    // При перевыделении памяти reserve() переносит существующие элементы — O(n).
    values.reserve(8);
    std::cout << "После reserve(8): size=" << values.size()
              << ", capacity=" << values.capacity() << '\n';

    // Здесь место уже есть, поэтому добавление в конец — O(1).
    // В общем случае push_back() — амортизированное O(1), при перевыделении — O(n).
    values.push_back(50);
    std::cout << "После push_back(50): ";
    print(values);

    // Поиск позиции по значению — O(n).
    auto position = std::find(values.begin(), values.end(), 30);
    if (position != values.end()) {
        // Вставка перед найденным элементом сдвигает последующие элементы — O(n).
        values.insert(position, 25);
        // После вставки position больше не используем: он стал недействительным.
    }
    std::cout << "После вставки 25 перед 30: ";
    print(values);

    auto found = std::find(values.begin(), values.end(), 40);
    if (found != values.end()) {
        // Для vector вычисление расстояния между итераторами — O(1).
        std::cout << "Линейный поиск 40: индекс "
                  << std::distance(values.begin(), found) << '\n';
    }

    // Для двоичного поиска данные должны быть упорядочены.
    // Здесь после всех операций числа остались отсортированными.
    // lower_bound() для vector — O(log n): возвращает первый элемент >= 40.
    auto boundary = std::lower_bound(values.begin(), values.end(), 40);
    if (boundary != values.end() && *boundary == 40) {
        std::cout << "Двоичный поиск нашёл: " << *boundary << '\n';
    }

    // Заново ищем позицию перед изменением контейнера.
    auto to_erase = std::find(values.begin(), values.end(), 20);
    if (to_erase != values.end()) {
        // Удаление сдвигает последующие элементы — O(n).
        values.erase(to_erase);
    }
    // Итераторы found и boundary после этого изменения больше не используем.
    std::cout << "После удаления 20: ";
    print(values);
}

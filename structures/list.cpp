#include <algorithm>
#include <iostream>
#include <iterator>
#include <list>

void print(const std::list<int>& values) {
    for (int value : values) {
        std::cout << value << ' ';
    }
    std::cout << '\n';
}

int main() {
    std::list<int> values{10, 20, 30, 40};
    std::cout << "Исходный list: ";
    print(values);

    // У list нет operator[]. До третьего элемента нужно пройти два шага.
    // std::next(begin, k) для list — O(k), в худшем случае O(n).
    auto third = std::next(values.begin(), 2);
    std::cout << "Элемент с индексом 2 после прохода: " << *third << '\n';

    // Добавление в начало и конец — O(1).
    values.push_front(5);
    values.push_back(50);
    std::cout << "После push_front(5) и push_back(50): ";
    print(values);

    // Поиск позиции по значению — O(n).
    auto position = std::find(values.begin(), values.end(), 30);
    if (position != values.end()) {
        // Вставка одного элемента перед готовым итератором — O(1).
        // Суммарно поиск + вставка в этом примере — O(n).
        values.insert(position, 25);
        std::cout << "После вставки 25 перед 30: ";
        print(values);

        // Вставка не делает итераторы на существующие элементы недействительными.
        std::cout << "Сохранённый итератор всё ещё указывает на: " << *position << '\n';

        // Удаление одного элемента по готовому итератору — O(1).
        values.erase(position);
        // position указывал на удалённый элемент: теперь его использовать нельзя.
    }
    std::cout << "После удаления 30: ";
    print(values);

    // Поиск по значению требует последовательного обхода — O(n).
    auto found = std::find(values.begin(), values.end(), 40);
    if (found != values.end()) {
        std::cout << "Линейный поиск нашёл: " << *found << '\n';
    }

    // У list двунаправленные итераторы: можно сделать шаг назад от end().
    // Список здесь непустой, поэтому это допустимо.
    std::cout << "Последний элемент: " << *std::prev(values.end()) << '\n';
}

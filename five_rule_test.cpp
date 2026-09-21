#include "five_rule_test.hpp"

#include <algorithm>

// конструктор копирования
//
// Buffer a(10);
// Buffer b = a;
Buffer::Buffer(const Buffer& other) : data(new int[other.size]), size(other.size) {
    std::copy(other.data, other.data + size, data);
}

// оператор копирующего присваивания
// b.operator=(a);
// результат Buffer b = a;
Buffer& Buffer::operator=(const Buffer& other) {
    // копируем данные из other в *this
    // сначала выделяем и копируем, потом освобождаем: если new бросит, *this не пострадает
    int* fresh = new int[other.size];                      // выделяем новую память
    std::copy(other.data, other.data + other.size, fresh); // копируем данные a -> новая память
    delete[] data;                                         // освобождаем старые данные
    data = fresh;                                          // b владеет новой памятью
    size = other.size;                                     // берем размер a
    return *this;                                          // возращаем b
}

// конструктор перемещения
//
// Пример использования
// Buffer a(100);
// Buffer b = std::move(a);
Buffer::Buffer(Buffer&& other) noexcept : data(other.data), size(other.size) {
    other.data = nullptr;
    other.size = 0;
}

// перемещающее присваивание
//
// Пример использования
// Buffer a(10);
// Buffer b(20);
// b = std::move(a);
Buffer& Buffer::operator=(Buffer&& other) noexcept {
    if (this != &other) {
        delete[] data;
        data = other.data;
        size = other.size;
        other.data = nullptr;
        other.size = 0;
    }
    return *this;
}

// оператор доступа: чтение и запись
//
// Buffer a(5);
// a[0] = 42;
int& Buffer::operator[](std::size_t i) {
    return data[i];
}

// const-версия: только чтение
// компилятор выбирает ее сам, если объект const
//
// const Buffer& ref = a;
// int x = ref[0]; // ок
// ref[0] = 1;     // ошибка компиляции: const int& нельзя менять
const int& Buffer::operator[](std::size_t i) const {
    return data[i];
}

[[nodiscard]] std::size_t Buffer::get_size() const {
    return size;
}

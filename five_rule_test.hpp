#pragma once
#include <cstddef>

class Buffer {
private:
    int* data = nullptr;

    // std::size_t — беззнаковый целый тип для размеров и индексов (объявлен в <cstddef>)
    // именно его возвращает sizeof и принимает new[]; на 64-битной системе это 64 бита,
    // поэтому в него гарантированно помещается размер любого объекта в памяти
    // беззнаковый = отрицательных значений нет: 0 - 1 даст не -1, а огромное число
    std::size_t size = 0;

public:
    // explicit = запрет неявного вызова конструктора для преобразования типов
    // Ставьте explicit почти на все конструкторы с одним аргументом
    // Всегда ставьте explicit на операторы преобразования типа (operator int, operator bool)
    explicit Buffer(std::size_t size) : data(new int[size]), size(size) {}

    ~Buffer() { delete[] data; }

    // конструктор копирования
    Buffer(const Buffer& other);

    // оператор копирующего присваивания
    Buffer& operator=(const Buffer& other);

    // конструктор перемещения
    // noexcept функция гарантированно не выбрасывает исключений
    Buffer(Buffer&&) noexcept;

    // перемещающее присваивание
    Buffer& operator=(Buffer&& other) noexcept;

    // оператор доступа к данным (чтение и запись)
    //
    // вызывается для обычного объекта: Buffer a(5); a[0] = 42;
    int& operator[](std::size_t i);

    // const-версия оператора доступа (только чтение)
    //
    // const после скобок = метод не меняет объект, поэтому его можно вызвать у const-объекта
    // вызывается для const Buffer / const Buffer&: возвращает const int&, записать через него нельзя
    // без этой версии buf[i] для const Buffer& не скомпилируется
    const int& operator[](std::size_t i) const;

    // [[nodiscard]] — это атрибут в C++ (появился в C++17, расширен в C++20), который заставляет
    // компилятор выдавать предупреждение (warning), если программист игнорирует возвращаемое
    // значение функции или результат создания объекта
    [[nodiscard]] std::size_t get_size() const;
};
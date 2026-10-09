#include <functional>
#include <iostream>

namespace simple_function {
void print(int index) {
    while (index--) {
        std::cout << index << " ";
    }
    std::cout << std::endl;
}
// std::function Тип-обёртка для вызываемого объекта

void demo() {
    // 1. храним свободную функцию
    std::function<void(int)> display10 = print;
    display10(10);

    // 2. связываем функцию и параметр и потом передаем function с помощью std::bind
    // std::bind — создаёт вызываемый объект с заранее привязанными аргументами
    std::function<void()> display30 = std::bind(print, 30);
    // вызов сохраненного объекта
    display30();

    // 3. современный способ - храним лямбду (С++11 - введение лямбды)
    std::function<void()> display20 = []() { print(20); };
    display20();

    // 4. обойдемся без std::function
    auto display50 = []() { print(50); };
    display50();
}
} // namespace simple_function

class Foo {
public:
    Foo(int i) : i_(i) {}
    void print_add(int value) const { std::cout << i_ + value << std::endl; }
    int i_;
};


namespace class_function {
void demo() {
    // 5. храним указатель на метод класса
    // const Foo& ссылка на объект, для которого вызываем метод
    // добавили класс как параметр, т.к. метод не статический
    std::function<void(const Foo&, int)> add_display = &Foo::print_add;
    const Foo foo(12345);
    add_display(foo, 1);

    // 6. храним указатель на поле класса
    std::function<int(const Foo&)> field = &Foo::i_;
    std::cout << field(foo) << std::endl;

    // 7. привязываем метод и объект (foo)
    using std::placeholders::_1; // аргумент будет передан позднее
    std::function<void(int)> display_object =
        std::bind(&Foo::print_add, foo, _1); // храним копию объекта
    display_object(2);

    // 8. привязываем указатель и объект (&foo)
    std::function<void(int)> display_pointer =
        std::bind(&Foo::print_add, &foo, _1); // храним указатель на объект
    display_pointer(3);
}
} // namespace class_function


namespace lambda {
// [capture] (parameters) -> return_type { body }
// capture - переменные из внешней области видимости доступны внутри лямбды

// рекурсивная лямбда для вычисления факториала
// Факториал натурального числа n — это произведение всех натуральных чисел от 1 до n
// включительно, которое обозначается как n!
auto factorial = [](int n) {
    std::function<int(int)> fac = [&](int k) { return (k < 2) ? 1 : (k * fac(k - 1)); };
    return fac(n);
};

void demo() {
    for (int i{5}; i != 8; ++i) {
        std::cout << i << "! = " << factorial(i) << ";  ";
    }
    std::cout << std::endl;
}
} // namespace lambda

int main() {
    simple_function::demo();
    class_function::demo();
    lambda::demo();
}

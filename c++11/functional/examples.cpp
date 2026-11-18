#include <functional>
#include <iostream>
#include <utility>
#include <vector>

int subtract(int left, int right) { return left - right; }

struct Multiplier {
    int factor;
    int operator()(int value) const { return factor * value; }
};

struct Counter {
    int total;
    void add(int value) { total += value; }
};

// Один обработчик события. Пустой обработчик означает отсутствие подписки.
class Button {
public:
    using Handler = std::function<void(int)>;

    void set_handler(Handler handler) { handler_ = std::move(handler); }

    void click(int value) const {
        if (handler_) {
            handler_(value);
        }
    }

private:
    Handler handler_;
};

void function_examples() {
    std::function<int(int, int)> operation = subtract;
    std::cout << "function: " << operation(10, 3) << '\n';

    std::function<int(int)> transform = Multiplier{3};
    std::cout << "functor: " << transform(4) << '\n';
    const int offset = 5;
    transform = [offset](int value) { return offset + value; };
    std::cout << "lambda: " << transform(4) << '\n';

    // Разные конкретные типы хранятся за одной сигнатурой int(int).
    const std::vector<std::function<int(int)>> operations = {
        Multiplier{2}, [offset](int value) { return offset + value; }};
    std::cout << "pipeline: ";
    int value = 3;
    for (const auto& step : operations) {
        value = step(value);
    }
    std::cout << value << '\n';

    std::function<void()> empty;
    std::cout << "empty: " << !empty << '\n';
    try {
        empty(); // Контролируемо показываем исключение, а не UB.
    } catch (const std::bad_function_call&) {
        std::cout << "caught bad_function_call\n";
    }

    // Копии обёртки содержат независимые копии состояния этой лямбды.
    std::function<int()> next = [value]() mutable { return ++value; };
    auto next_copy = next;
    std::cout << "owned state: " << next() << ' ' << next_copy() << '\n';
}

void bind_examples() {
    using std::placeholders::_1;
    using std::placeholders::_2;

    auto from_ten = std::bind(subtract, 10, _1);
    auto reverse = std::bind(subtract, _2, _1);
    std::cout << "bind: " << from_ten(3) << ' ' << reverse(3, 10) << '\n';

    // Та же операция через лямбду; std::function здесь не нужен.
    auto from_ten_lambda = [](int value) { return subtract(10, value); };
    std::cout << "lambda equivalent: " << from_ten_lambda(3) << '\n';

    Counter counter{0};
    auto copied = std::bind(&Counter::add, counter, _1);
    auto referenced = std::bind(&Counter::add, std::ref(counter), _1);
    copied(5); // Меняет только сохранённую внутри bind копию.
    std::cout << "after copy: " << counter.total << '\n';
    referenced(5);
    std::cout << "after ref: " << counter.total << '\n';

    // Указатель на метод сам по себе не содержит объект.
    void (Counter::*method)(int) = &Counter::add;
    (counter.*method)(2);
    std::function<void(Counter&, int)> unbound = method;
    unbound(counter, 3);
    std::cout << "member calls: " << counter.total << '\n';
}

void delegate_example() {
    // counter создан раньше button: при разрушении порядок будет обратным.
    Counter counter{0};
    Button button;
    button.click(100); // Обработчика ещё нет.
    button.set_handler([&counter](int value) { counter.add(value); });
    button.click(4);
    button.click(6);
    std::cout << "delegate: " << counter.total << '\n';
    button.set_handler(nullptr); // Отписка.
    button.click(100);
    std::cout << "after unsubscribe: " << counter.total << '\n';
}

int main() {
    function_examples();
    bind_examples();
    delegate_example();
}

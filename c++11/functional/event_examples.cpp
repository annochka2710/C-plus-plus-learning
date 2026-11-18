#include "event.hpp"

#include <iostream>

struct Counter {
    int total = 0;
    void add(int value) { total += value; }
};

int main() {
    Counter counter;
    Event changed;

    const auto counter_id = changed.subscribe(
        [&counter](int value) { counter.add(value); });
    const auto log_id = changed.subscribe(
        [](int value) { std::cout << "log: " << value << '\n'; });

    changed.emit(2); // Оба подписчика.
    changed.emit(3);
    std::cout << "total: " << counter.total << '\n'; // 5.

    changed.unsubscribe(log_id);
    changed.emit(4); // Только счётчик.
    std::cout << "after log unsubscribe: " << counter.total << '\n'; // 9.

    changed.unsubscribe(counter_id);
    changed.emit(100); // Подписчиков нет.
    std::cout << "after all unsubscribe: " << counter.total << '\n'; // 9.

    Event::SubscriptionId once_id = 0;
    once_id = changed.subscribe([&changed, &once_id](int value) {
        std::cout << "once: " << value << '\n';
        changed.unsubscribe(once_id); // Можно отписаться внутри обработчика.
    });
    changed.emit(7);
    changed.emit(8); // Одноразовый обработчик уже удалён.
}

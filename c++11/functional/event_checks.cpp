#include "event.hpp"

#include <iostream>
#include <stdexcept>
#include <vector>

void require(bool condition, const char* message) {
    if (!condition) {
        throw std::logic_error(message);
    }
}

int main() {
    Event event;
    event.emit(0); // Пустое событие допустимо.
    std::vector<int> calls;
    Event::SubscriptionId first = 0;
    Event::SubscriptionId second = 0;
    first = event.subscribe([&](int value) {
        calls.push_back(value);
        event.unsubscribe(first); // Самоотписка безопасна.
        event.unsubscribe(second); // Второй не должен получить это событие.
        event.subscribe([&calls](int next) { calls.push_back(10 * next); });
    });
    second = event.subscribe([&calls](int value) { calls.push_back(100 * value); });
    event.emit(1);
    require(calls == std::vector<int>{1}, "subscribe/unsubscribe during emit");
    event.emit(2);
    require(calls == std::vector<int>({1, 20}), "new handler on next emit");
    require(!event.unsubscribe(first), "repeated unsubscribe must return false");
    require(!event.unsubscribe(0), "unknown subscription must return false");

    Event stateful;
    int count = 0;
    int observed = 0;
    stateful.subscribe([count, &observed](int) mutable { observed = ++count; });
    stateful.emit(0);
    stateful.emit(0);
    require(observed == 2, "mutable callback state must survive emit");

    bool rejected_empty = false;
    try {
        stateful.subscribe(nullptr);
    } catch (const std::invalid_argument&) {
        rejected_empty = true;
    }
    require(rejected_empty, "empty callback must be rejected");

    Event recursive;
    std::vector<int> nested;
    recursive.subscribe([&](int value) {
        nested.push_back(value);
        if (value == 1) {
            recursive.emit(2);
        }
    });
    recursive.emit(1);
    require(nested == std::vector<int>({1, 2}), "nested emission");

    Event throwing;
    int reached = 0;
    const auto throwing_id = throwing.subscribe([](int) {
        throw std::runtime_error("handler failed");
    });
    throwing.subscribe([&reached](int) { ++reached; });
    bool propagated = false;
    try {
        throwing.emit(0);
    } catch (const std::runtime_error&) {
        propagated = true;
    }
    require(propagated && reached == 0, "exception stops current emission");
    throwing.unsubscribe(throwing_id);
    throwing.emit(0);
    require(reached == 1, "event usable after handler exception");
    std::cout << "Event checks passed\n";
}

#ifndef CPP11_LEARNING_EVENT_HPP
#define CPP11_LEARNING_EVENT_HPP

#include <cstddef>
#include <functional>
#include <limits>
#include <map>
#include <memory>
#include <stdexcept>
#include <utility>
#include <vector>

// Учебное синхронное событие с одним аргументом int, для одного потока.
class Event {
public:
    using Handler = std::function<void(int)>;
    using SubscriptionId = std::size_t;

    Event() = default;
    Event(const Event&) = delete;
    Event& operator=(const Event&) = delete;
    Event(Event&&) = delete;
    Event& operator=(Event&&) = delete;

    SubscriptionId subscribe(Handler handler) {
        if (!handler) {
            throw std::invalid_argument("Empty event handler");
        }
        if (next_id_ == std::numeric_limits<SubscriptionId>::max()) {
            throw std::overflow_error("Subscription IDs exhausted");
        }
        const SubscriptionId id = next_id_;
        slots_.emplace(id, std::make_shared<Slot>(std::move(handler)));
        ++next_id_;
        return id;
    }

    bool unsubscribe(SubscriptionId id) {
        const auto found = slots_.find(id);
        if (found == slots_.end()) {
            return false;
        }
        // Текущий emit() может держать эту запись в своём снимке.
        found->second->active = false;
        slots_.erase(found);
        return true;
    }

    void emit(int value) {
        // Копируем указатели на записи, а не сами std::function.
        // Это сохраняет mutable-состояние обработчиков между вызовами.
        std::vector<std::shared_ptr<Slot>> snapshot;
        snapshot.reserve(slots_.size());
        for (const auto& entry : slots_) {
            snapshot.push_back(entry.second);
        }
        for (const auto& slot : snapshot) {
            if (slot->active) {
                slot->handler(value);
            }
        }
    }

private:
    struct Slot {
        explicit Slot(Handler callback) : handler(std::move(callback)) {}
        Handler handler;
        bool active = true;
    };

    SubscriptionId next_id_ = 1;
    std::map<SubscriptionId, std::shared_ptr<Slot>> slots_;
};

#endif

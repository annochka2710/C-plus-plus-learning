#ifndef INTERFACES_H
#define INTERFACES_H

#include <vector>
#include <functional>

using CallBack = std::function<void(int, int)>;

// Отправитель
class Producer {
public:
    // добавляем колбек в список
    // это значит - подписаться
    void subscribe(const CallBack& cb) {
        callbacks_.push_back(cb);
    }
protected:
    // по очереди рассылает колбеки всем подписчикам
    void notify(const int& value, const int& channel) {
        for(const auto& cb : callbacks_) {
            cb(value, channel);
        }
    }
private:
    std::vector<CallBack> callbacks_; // храним список колбеков
};

// Приемник
class Consumer {
public:
    virtual ~Consumer() = default;

    // что приемник делает с полученными данным
    virtual void show(int value, int channel) = 0;
protected:
    Consumer() = default;
    Consumer(const Consumer&) = default; 
    Consumer(Consumer&&) = default;
    Consumer& operator=(const Consumer&) = default;
    Consumer& operator=(Consumer&&) = default;
};

// Producer ничего не знает о классе Consumer
class Binder {
public:
    // соединяем одно с другим
    // на отправителя подписываем лямбду
    static void connect(Producer& prod, Consumer& cons) {
        prod.subscribe([&](int value, int channel){
            cons.show(value, channel);
        });
    }
};

#endif

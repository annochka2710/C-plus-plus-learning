#ifndef TRANSPONDER_H
#define TRANSPONDER_H

#include "interfaces.h"
#include <iostream>
#include <memory>
#include <queue>
#include <utility>

class Word {
public:
    using CallBack = void (*)(void*);
    Word(CallBack cb = nullptr, void* param = nullptr) : cb_(cb), param_(param) {}
    void setCallBack(CallBack cb, void* param) {
        cb_ = cb;
        param_ = param;
    }
    void simulateCallBack(int value) {
        value_ = value;
        if (cb_ != nullptr) {
            cb_(param_);
        }
    }
    [[nodiscard]] const int& get() const { return value_; }

private:
    CallBack cb_;
    void* param_;
    int value_{};
};

// Вспомогательный функтор
struct FunctionObject {
    FunctionObject(std::function<void(int)> cb) : cb_(std::move(cb)) {}
    void operator()(int ch) const { cb_(ch); }
    std::function<void(int)> cb_;
};

// Колбек для выдачи в канал 0
void onWord0Ready(void* context) {
    auto* pFunctor = static_cast<FunctionObject*>(context);
    (*pFunctor)(0);
}

// Колбек для выдачи в канал 1
void onWord1Ready(void* context) {
    auto* pFunctor = static_cast<FunctionObject*>(context);
    (*pFunctor)(1);
}

// Посредник: принимает данные как Consumer и передаёт дальше как Producer.
// Два пути выдачи данных подписчикам:
//   1) эхо:        receive -> очередь q_[channel] -> forwardQueued -> notify
//   2) по таймеру: onTimer0 -> Word::simulateCallBack -> onWord0Ready(void*)
//                  -> FunctionObject -> лямбда -> notify
// void* нужен, потому что Word умеет вызывать только C-функцию
class Transponder : public Producer, public Consumer {
public:
    Transponder() {
        w0 = std::make_unique<Word>();
        f0 = std::make_unique<FunctionObject>(
            [this](int channel) { this->notify(w0->get(), channel); });
        w0->setCallBack(onWord0Ready, f0.get());

        w1 = std::make_unique<Word>();
        f1 = std::make_unique<FunctionObject>(
            [this](int channel) { this->notify(w1->get(), channel); });
        w1->setCallBack(onWord1Ready, f1.get());
    }
    // эхо: достаём по одному значению из каждой очереди и отправляем подписчикам
    void forwardQueued() {
        for (int i = 0; i < 2; i++) {
            if (!q_[i].empty()) {
                const auto& value = q_[i].front();
                Producer::notify(value, i);
                q_[i].pop();
            }
        }
    }
    // приём от Reader: сохраняем значение в очередь своего канала
    void receive(int value, int channel) override {
        std::cout << "Transponder: " << value << " - " << channel << std::endl;
        q_[channel].push(value);
    }
    // имитация срабатывания таймера: "железо" выдаёт значение в канал 0 или 1
    void onTimer0(int value) { w0->simulateCallBack(value); }
    void onTimer1(int value) { w1->simulateCallBack(value); }

private:
    std::queue<int> q_[2]; // входные каналы 0 и 1
    std::unique_ptr<FunctionObject> f0;
    std::unique_ptr<FunctionObject> f1;
    std::unique_ptr<Word> w0; // слово для вых канала 0
    std::unique_ptr<Word> w1; // слово для вых канала 1
};

#endif

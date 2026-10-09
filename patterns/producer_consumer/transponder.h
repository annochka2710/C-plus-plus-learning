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
void WriteWord0(void* context) {
    auto* pFunctor = static_cast<FunctionObject*>(context);
    (*pFunctor)(0);
}

// Колбек для выдачи в канал 1
void WriteWord1(void* context) {
    auto* pFunctor = static_cast<FunctionObject*>(context);
    (*pFunctor)(1);
}

class Transponder : public Producer, public Consumer {
public:
    Transponder() {
        w0 = std::make_unique<Word>();
        f0 = std::make_unique<FunctionObject>(
            [this](int channel) { this->notify(w0->get(), channel); });
        w0->setCallBack(WriteWord0, f0.get());

        w1 = std::make_unique<Word>();
        f1 = std::make_unique<FunctionObject>(
            [this](int channel) { this->notify(w1->get(), channel); });
        w1->setCallBack(WriteWord1, f1.get());
    }
    void exec() {
        // эхо
        for (int i = 0; i < 2; i++) {
            if (!q_[i].empty()) {
                const auto& value = q_[i].front();
                Producer::notify(value, i);
                q_[i].pop();
            }
        }
    }
    void show(int value, int channel) override {
        std::cout << "Transponder: " << value << " - " << channel << std::endl;
        q_[channel].push(value);
    }
    void simulateCallBack0(int value) { w0->simulateCallBack(value); }
    void simulateCallBack1(int value) { w1->simulateCallBack(value); }

private:
    std::queue<int> q_[2]; // входные каналы 0 и 1
    std::unique_ptr<FunctionObject> f0;
    std::unique_ptr<FunctionObject> f1;
    std::unique_ptr<Word> w0; // слово для вых канала 0
    std::unique_ptr<Word> w1; // слово для вых канала 1
};

#endif

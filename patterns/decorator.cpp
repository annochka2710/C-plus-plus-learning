// По мотивам C++-примера из Википедии; объяснение и источник — в decorator.md.
#include <iostream>
#include <memory>
#include <utility>

class IComponent {
public:
    virtual ~IComponent() = default;
    virtual void operation() = 0;
};

class Component : public IComponent {
public:
    void operation() override {
        std::cout << "World!\n";
    }
};

// Обёртка реализует тот же интерфейс, что и вложенный объект.
class DecoratorOne : public IComponent {
public:
    // Предусловие: component не должен быть nullptr.
    explicit DecoratorOne(std::shared_ptr<IComponent> component)
        : component_(std::move(component)) {}

    void operation() override {
        std::cout << ", ";
        component_->operation();
    }

private:
    std::shared_ptr<IComponent> component_;
};

class DecoratorTwo : public IComponent {
public:
    // Вложенным объектом может быть и компонент, и другой декоратор.
    // Предусловие: component не должен быть nullptr.
    explicit DecoratorTwo(std::shared_ptr<IComponent> component)
        : component_(std::move(component)) {}

    void operation() override {
        std::cout << "Hello";
        component_->operation();
    }

private:
    std::shared_ptr<IComponent> component_;
};

// Клиент работает через общий интерфейс, не зная состава цепочки.
void Operation(IComponent& component) {
    component.operation();
}

int main() {
    DecoratorTwo greeting(
        std::make_shared<DecoratorOne>(std::make_shared<Component>()));

    Operation(greeting); // Hello, World!
}

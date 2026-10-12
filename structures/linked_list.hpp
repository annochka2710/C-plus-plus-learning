/// TODO: расписать, какие операции быстро, а какие медленно

#pragma once

#include <cstddef>

// Структура одного узла
struct Node {
    int data;   // данные которые храним
    Node* next = nullptr; // указатель на следующий узел в списке

    explicit Node(int value) : data(value) {}
};

// Односвязный список std::forward_list
//
// Каждый узел указывает на следующий элемент
// Последний указывает на nullptr
// Двигаться можно только вперед
class SinglyLinkedList {
public:
    // Конструктор по умолчанию
    SinglyLinkedList() = default;

    ~SinglyLinkedList();

    // копирующий конструктор (глубокая копия) - пока запрещен
    SinglyLinkedList(const SinglyLinkedList&) = delete;

    // Оператор присваивания копированием - пока запрещен
    SinglyLinkedList& operator=(const SinglyLinkedList&) = delete;

    // перемещающий конструктор - пока запрещен
    SinglyLinkedList(SinglyLinkedList&&) = delete;

    // Оператор присваивания с перемещением - пока запрещен
    SinglyLinkedList& operator=(SinglyLinkedList&&) = delete;

    // добавить в начало списка
    void push_front(int value);

    // добавить в конец списка
    void push_back(int value);

    [[nodiscard]] bool is_empty() const;

    [[nodiscard]] std::size_t size() const;

    void print() const;

    // удаление
    void pop_front();

    void pop_back();

    // доступ
    [[nodiscard]] int front() const;

    [[nodiscard]] int back() const;

    // освободить все узлы
    void clear();

    // работа с серединой
    [[nodiscard]] Node* find_value(int value) const;

    void insert_after(Node* node, int value);

    // удалить узел, следующий за node
    void erase_after(Node* node);

    // удаление всех узлов с таким значением
    void remove_value(int value);

private:
    Node* head_ = nullptr;
    Node* tail_ = nullptr; // можно не хранить
    std::size_t size_ = 0; // можно не хранить
};

// Двусвязные список std::list
//
// Каждый узел хранит два указателя
// Последний указывает на nullptr
// Двигаться можно в двух направлениях и быстрее
class DoublyLinkedList {
    int data;       // данные которые храним
    Node* next;     // указатель на следующий узел в списке
    Node* previous; // указатель на предыдущий
};

// Кольцевой список
//
// Последний элемент вместо nullptr указывает обратно
// на первый (или первый на последний), замыкая список в круг.
class CircularLinkedList {
    int data;       // данные которые храним
    Node* next;     // указатель на следующий узел в списке
    Node* previous; // указатель на предыдущий
};

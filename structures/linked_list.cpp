/// TODO: задачи для практики
/// reverse();
/// поиск середины;
/// поиск цикла.

#include "linked_list.hpp"

#include <iostream>

// ===== SinglyLinkedList =====

SinglyLinkedList::~SinglyLinkedList() {
    // TODO: освободить все узлы (можно вызвать clear())
    clear();
}

// O(1)
void SinglyLinkedList::push_front(int value) {
    Node* new_node = new Node(value);
    new_node->next = head_; // связываем новый узел со старым первым
    head_ = new_node;       // перемещаем head на новый узел
    if (tail_ == nullptr) {
        tail_ = new_node;
    }
    size_++;
}

// O(1) константное время у двусвязного списка
// O(N) константное время у односвязного списка, если есть только head_
void SinglyLinkedList::push_back(int value) {
    Node* new_node = new Node(value);
    // список пустой
    if (is_empty()) {
        head_ = new_node;
        tail_ = new_node;
    } // в списке есть элементы
    else {
        tail_->next = new_node; // next of last node updated
    }
    tail_ = new_node; // tail_'s pointer points to a new node
    size_++;
}

bool SinglyLinkedList::is_empty() const {
    return (head_ == nullptr);
}

std::size_t SinglyLinkedList::size() const {
    return size_;
}

// O(N)
void SinglyLinkedList::print() const {
    Node* current = head_;       // взяли указатель
    while (current != nullptr) { // останавливаемся после tail_
        std::cout << current->data << " ";
        // шагаем к следующему
        current = current->next;
    }
}

void SinglyLinkedList::pop_front() {}

void SinglyLinkedList::pop_back() {
    // TODO
}

int SinglyLinkedList::front() const {
    // TODO: что делать, если список пустой?
    return 0;
}

int SinglyLinkedList::back() const {
    // TODO: что делать, если список пустой?
    return 0;
}

// удалить все элементы
// O(N)
void SinglyLinkedList::clear() {
    while (head_ != nullptr) {
        Node* next = head_->next; // запомнили куда идти
        delete head_;       // т.к. после delete читать head_->next нельзя
        head_ = next;
    }
    // head_ уже nullptr после цикла
    tail_ = nullptr;
    size_ = 0;
}

Node* SinglyLinkedList::find_value(int value) const {
    // TODO
    return nullptr;
}

void SinglyLinkedList::insert_after(Node* node, int value) {
    // TODO
}

void SinglyLinkedList::erase_after(Node* node) {
    // TODO
}

void SinglyLinkedList::remove_value(int value) {
    // TODO
}

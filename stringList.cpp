#include "stringList.h"
namespace stringList
{
    // Constructors
    node::node(const stos::string& data) {
        this->data = data;
        this->next = nullptr;
        this->prev = nullptr;
    }

    list::list() {
        head = nullptr;
        tail = nullptr;
        length = 0;
    }

    list::~list() {
        while (!empty()) {
            pop_back();
        }
    }

    list::list(const std::initializer_list<stos::string>& data) {
        for (const stos::string& item : data) {
            push_back(item);
        }
    }

    // Functions

    bool list::empty() const {
        return head == nullptr;
    }

    void list::push_back(const stos::string& data) {
        node* newNode = new node(data);
        if (tail == nullptr) {
            head = tail = newNode;
        }
        else {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }
        length++;
    }

    size_t list::size() const {
        return length;
    }

    const stos::string& list::back() const {
        if (tail != nullptr) {
            return tail->data;
        }
        throw std::runtime_error("List is empty");
    }

    void list::pop_back() {
        if (tail == nullptr) {
            return;
        }

        node* lastNode = tail;
        tail = tail->prev;
        if (tail != nullptr) {
            tail->next = nullptr;
        }
        else {
            head = nullptr;
        }
        delete lastNode;
        length--;
    }

    //stos::string& list::at(int index) const {
    //    if (empty()) {
    //        throw std::out_of_range("List is empty");
    //    }

    //    if (index < 0) {
    //        throw std::out_of_range("Index cannot be negative");
    //    }

    //    node* current = head;
    //    int count = 0;
    //    while (current != nullptr && count < index) {
    //        current = current->next;
    //        ++count;
    //    }

    //    if (current == nullptr) {
    //        throw std::out_of_range("Index out of bounds");
    //    }

    //    return current->data;
    //}

    const node* list::getHead() const
    {
        return head;
    }

    const node* list::getTail() const
    {
        return tail;
    }

    const node* list::getNext(const node* current) const
    {
        return current ? current->next : nullptr;
    }

    const node* list::getPrev(const node* current) const
    {
        return current ? current->prev : nullptr;
    }

}

#include "intList.h"
namespace intList
{
    // Constructors
    node::node(int data) {
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

    // Functions

    bool list::empty() const {
        return head == nullptr;
    }

    void list::push_back(int data) { //double
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

    size_t list::size() const { //double
        return length;
    }

    int list::back() const { //double
        if (tail != nullptr) {
            return tail->data;
        }
        throw std::runtime_error("List is empty");
    }

    void list::pop_back() { //double
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

    //int list::at(size_t index) const {
    //    if (empty()) {
    //        throw std::out_of_range("List is empty");
    //    }

    //    if (index < 0) {
    //        throw std::out_of_range("Index cannot be negative");
    //    }

    //    node* current = head;
    //    size_t count = 0;
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

    void testList()
    {
        intList::list test;
        test.push_back(20);
        test.push_back(15);
        test.push_back(10);
        test.pop_back();
        std::cout << test.size();
    }
}

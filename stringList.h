#pragma once
#include <iostream>
#include "string.h"
namespace stringList
{
    class node {
    public:
        stos::string data; // Change data type based on your needs (int, string, etc.)
        node* next = nullptr;
        node* prev = nullptr;

        // Constructor
        explicit node(const stos::string& data);
    };

    class list {
    private:
        node* head = nullptr;
        node* tail = nullptr;
        size_t length = 0;

    public:

        // Constructor
        list();
        explicit list(const std::initializer_list<stos::string>& data);
        ~list();

        list(const list&) = delete;

        //Functions
        // push.back()
        void push_back(const stos::string& data);

        // empty()
        bool empty() const;

        // size()
        size_t size() const;

        // back()
        const stos::string& back() const;

        // pop.back()
        void pop_back();

        // at()
        //stos::string& at(int index) const;

        // get the first node or nullptr if empty.
        const node* getHead() const;
        const node* getTail() const;

        // get the next node or nullptr.
        const node* getNext(const node* current) const;
        const node* getPrev(const node* current) const;

    };
    //void testList();
}




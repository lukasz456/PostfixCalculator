#pragma once
#include <iostream>
namespace intList
{
    class node {
    public:
        int data; // Change data type based on your needs (int, string, etc.)
        node* next;
        node* prev;

        // Constructor
        explicit node(int data);
    };

    class list {
    private:
        node* head;
        node* tail;
        size_t length;

    public:

        // Constructor
        list();
        ~list();

        list(const list&) = delete;

        //Functions
        // push.back()
        void push_back(int data);

        // empty()
        bool empty() const;

        // size()
        size_t size() const;

        // back()
        int back() const;

        // pop.back()
        void pop_back();

        // at()
        //int at(size_t index) const;

        // get the first node or nullptr if empty.
        const node* getHead() const;
        const node* getTail() const;

        // get the next node or nullptr.
        const node* getNext(const node* current) const;
        const node* getPrev(const node* current) const;
    };
    void testList();
}




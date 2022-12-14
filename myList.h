#ifndef _MYLIST_H
#define _MYLIST_H

#include<iostream>

using namespace std;

template <typename T>
class Node
{
    private:
        T elem; //data element
        Node* next; //Link (pointer) to the next Node
        Node* prev; //Link (pointer) to the previous Node
        template <typename T2> friend class MyList; //MyList is a friend
        
    public:
        Node(): next(NULL), prev(NULL)
        {}
        Node(T elem) : elem(elem),next(NULL), prev(NULL)
        {}
};
//==============================================================
template <typename T>
class MyList
{
    private:
        Node<T>* head;     // pointer to the head of List
        Node<T>* tail;     // pointer to the tail of List
    public:
        int size;
        MyList (); // empty list constructor
        ~MyList (); // destructor to clean up all nodes
        bool empty() const; // is list empty?
        const T& front() const; // get the value (element) from front Node<T> of list
        const T& back() const;  // get the value (element) from last Node<T> of the List
        void addBefore(Node<T> *ptr, const T& elem);     //add a new node before ptr
        void addFront(const T& elem); // add a new node to the front of list
        void addBack(const T & elem); //add a new node to the back of the list
        void removeFront(); // remove front node from list
        void removeBack();  // remove last node from list
        void erase(const T& elem); // remove last item from list

        
        //Iterator
        class iterator;   //Forwarding declaration of iterator class
        iterator begin()
        {
            return iterator(head->next);
        }
        iterator end()
        {
            return iterator(tail);
        }
        
        class iterator
        {
            private:
                Node <T>* ptr;
            public:
                using iterator_category = bidirectional_iterator_tag;
                using difference_type = ptrdiff_t;
                using value_type = T;
                using pointer = T*;
                using reference = T&;

                iterator(Node<T>* node)
                {
                    ptr = node;
                }
                T operator*()
                {
                    return ptr->elem;
                }
                iterator& operator++(int)
                {
                    ptr = ptr->next;
                    return *this;
                }
               
                iterator operator++()
                {
                    iterator temp = *this;
                    ptr = ptr->next;
                    return temp;
                }
                iterator& operator--()
                {
                    iterator temp = *this;
                    ptr = ptr->prev;
                    return temp;
                }
                bool operator==(const iterator& other) const
                {
                    return ptr == other.ptr;
                }
                bool operator!=(const iterator& other) const
                {
                    return ptr != other.ptr;
                }
            };
};

#endif /* myList_hpp */

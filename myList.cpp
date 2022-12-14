
#include<iostream>
#include<string>
#include<sstream>
#include<iomanip>
#include<exception>

#include "myList.h"
#include "flighthashtable.h"


using namespace std;

int size = 0;

template <typename T>
MyList<T>::MyList ()
{
    this->head = new Node<T>();
    this->tail = new Node<T>();
    this->head->next = tail;
    this->tail->prev = head;
    int size = 0;

}
//============================================================
template <typename T>
MyList<T>::~MyList () // destructor to clean up all nodes
{
    while(!empty())
        removeFront();
}
//============================================================
template <typename T>
bool MyList<T>::empty() const // is list empty?
{
    return this->head->next == tail;
}
//============================================================
template <typename T>
const T& MyList<T>::front() const // get front element
{
    if(!empty())
        return this->head->next->elem;
    else
        throw runtime_error("List is Empty");
}
//============================================================
template <typename T>
const T& MyList<T>::back() const // get front element
{
    if(!empty())
        return this->tail->prev->elem;
    else
        throw runtime_error("List is Empty");
}
//============================================================
template <typename T>
void MyList<T>::addBefore(Node<T> *ptr, const T& elem)
{
 if (head == nullptr)
    {
        head = new Node<T>(elem);
        tail = new Node<T>(elem);
        head->next = tail;
        tail ->prev = head;
        size++;

    }    
    else 
    {
        Node<T>* newNode = new Node<T>(elem);
        newNode->next = ptr;
        newNode->prev = ptr->prev;
        ptr->prev->next = newNode;
        ptr->prev = newNode;
        size++;

    }

}
//============================================================
template <typename T>
void MyList<T>::addFront(const T& elem) // add to front of list
{
    addBefore(this->head->next, elem);
}
//============================================================
template <typename T>
void MyList<T>::addBack(const T& elem) // add to Back of the list
{
    addBefore(this->tail, elem);
}
//============================================================
template <typename T>
void MyList<T>::removeFront() // remove front item from list
{
    if(!empty())
    {
        Node<T> *tmp = this->head->next;
        this->head->next = tmp->next;
        tmp->next->prev = head;
        delete tmp;
    }
}
//============================================================
template <typename T>
void MyList<T>::removeBack() // remove last item from list
{
    if(!empty())
    {
        Node<T> *tmp = this->tail->prev;
        this->tail->prev = tmp->prev;
        tmp->prev->next = tail;
        delete tmp;
    }
}

//============================================================
template <typename T>
void MyList<T>::erase(const T& elem) // remove last item from list
{
  
    Node<T> *tmp = this->head->next;
    while(tmp != this->tail)
    {
        if(tmp->elem == elem)
        {
            tmp->prev->next = tmp->next;
            tmp->next->prev = tmp->prev;
            delete tmp;
            break;
        }
        tmp = tmp->next;
    }
}

template class MyList<HashNode>;


#ifndef TABLE_CLASS_QUEUE_H
#define TABLE_CLASS_QUEUE_H
#include "LinkedList.h"

template <class T>
class Queue{
public:
    Queue():_head(NULL), _tail(NULL){}

    // Big Three
    ~Queue();
    Queue(const Queue<T>& other);
    Queue<T> &operator =(const Queue& rhs);

    // push new item to the rear
    void push(T item);

    // always pop item at the front
    T pop();

    // return true if the head is null
    bool empty();

    // return the item of the head
    T front();

    friend ostream& operator <<(ostream& outs, const Queue& q){
        return print_list(q._head, outs);

    }

private:
    node<T>* _head;
    node<T>* _tail;
};

// copy constructor
template <class T>
Queue<T>::Queue(const Queue<T>& other)
{
    this->_head = nullptr;
    this->_tail = copy_list(other._head, this->_head);
}

// assignment operator overload
template <class T>
Queue<T>& Queue<T>::operator =(const Queue& rhs)
{
    if(this->_head == rhs._head)
    {
        return *this;
    }
    this->_tail = copy_list(rhs._head, this->_head);
    return *this;
}

// push new item to the rear
template <class T>
void Queue<T>::push(T item)
{
    if(!_head)
    {
        insert_head(_head, item);
        _tail = _head;
    }
    else
    {
        insert_after(_head, _tail, item);
        _tail = _tail->_next;
    }
}

// always pop the item at front
template <class T>
T Queue<T>::pop()
{
    if(_head == _tail)
    {
        _tail = NULL;
    }
    return delete_head(_head);
}

// return true if the head is null
template <class T>
bool Queue<T>::empty()
{
    if(_head)
        return false;
    else
        return true;
}

// return the item of the head
template <class T>
T Queue<T>::front()
{
    return _head->_item;
}

// destructor
template <class T>
Queue<T>::~Queue()
{
    while(_head)
    {
        delete_head(_head);
    }
}

#endif //TABLE_CLASS_QUEUE_H

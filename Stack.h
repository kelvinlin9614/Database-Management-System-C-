#ifndef TABLE_CLASS_STACK_H
#define TABLE_CLASS_STACK_H
#include "LinkedList.h"

template <class T>
class Stack{
public:
    Stack():_top(NULL){}

    // Big Three
    ~Stack();
    Stack(const Stack<T>& other);
    Stack<T>& operator =(const Stack<T>& rhs);

    // push the new item at front
    void push(T item);

    // always pop the item at front
    T pop();

    // return the item of head(top)
    T top();

    // return true if head is null
    bool empty();

    friend ostream& operator << (ostream& outs, const Stack& s){
        return print_list(s._top, outs);
    }
private:
    node<T>* _top;
};

// copy constructor
template <class T>
Stack<T>::Stack(const Stack<T>& other)
{
    this->_top = NULL;
    copy_list(other._top, this->_top);
}

// assignment operator overload
template <class T>
Stack<T>& Stack<T>::operator =(const Stack<T>& rhs)
{
    if(this->_top == rhs._top)
    {
        return *this;
    }
    copy_list(rhs._top, this->_top);
    return *this;
}

// push the new item ar front
template <class T>
void Stack<T>::push(T item)
{
    insert_head(_top, item);
}

// always pop item at front
template <class T>
T Stack<T>::pop()
{
    T hold = _top->_item;
    delete_head(_top);
    return hold;
}

// return the item of the head
template <class T>
T Stack<T>::top()
{
    return _top->_item;
}

// return true if head is null
template <class T>
bool Stack<T>::empty()
{
    return _top == nullptr;
}

// destructor
template <class T>
Stack<T>::~Stack()
{
    while(_top)
    {
        delete_head(_top);
    }
}

#endif //TABLE_CLASS_STACK_H

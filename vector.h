#ifndef TABLE_CLASS_VECTOR_H
#define TABLE_CLASS_VECTOR_H

#include <iostream>
#include <iomanip>
#include "vector_function.h"

using namespace std;

template <typename T>
class Vector
{
public:
    Vector(unsigned int capacity = 100);

    //big three
    Vector(const Vector& other);
    Vector& operator = (const Vector& rhs);
    ~Vector();

    //member access functions:
    const T& operator [](const int index) const;
    T& operator [](const int index);
    T& at(int index);
    const T& at(int index) const;
    T& front() const;
    T& back() const;

    //Push and Pop functions:
    Vector& operator += (const T& item);
    void push_back(const T& item);
    void pop_back();

    //Insert and Erase
    void insert(int insert_here,const T& insert_this);
    void erase(int erase_index);
    int index_of(const T& item);

    //size and capacity
    void set_size(int size);
    void set_capacity(int capacity);
    int size() const {return _size;}
    int capacity() const {return _capacity;}
    bool empty() const;

    template <typename U>
    friend ostream& operator << (ostream& outs, const Vector<U>& print_me);

private:
    int _size;
    int _capacity;
    T* _array;
};

//CTOR
template <typename T>
Vector<T>::Vector(unsigned int capacity)
{
    _capacity = capacity;
    _size = 0;
    _array = new T[_capacity];
}

//big three
template <typename T>
Vector<T>::Vector(const Vector& rhs)
{
    _size = rhs._size;
    _capacity = rhs._capacity;
    _array = new T[_capacity];
    copy_list_vector(_array, rhs._array, _size);
}

template <typename T>
Vector<T>& Vector<T>::operator = (const Vector& rhs)
{
    if (_array != nullptr)
        delete [] _array;
    _size = rhs._size;
    _capacity = rhs._capacity;
    _array = new T[_capacity];
    copy_list_vector(_array, rhs._array, _size);
    return *this;
}

template <typename T>
Vector<T>:: ~Vector()
{
    delete[] _array;
    _array = nullptr;
}

template <typename T>
T& Vector<T>::at(int index)
{
    if (index < capacity())
    {
        T*temp = _array+index;
        return *temp;
    }
}

template <typename T>
const T& Vector<T>::at(int index) const
{
    if (index < capacity())
    {
        T*temp = _array+index;
        return *temp;
    }
}

template <typename T>
const T& Vector<T>::operator [](const int index) const
{
    if (index < capacity())
        return at(index);
}

template <typename T>
T& Vector<T>:: operator [](const int index)
{
    if (index < capacity())
        return at(index);
}

template <typename T>
T& Vector<T>::front() const
{
    T*temp = _array;
    return *temp;
}

template <typename T>
T& Vector<T>::back() const
{
    // get the last element
    T*temp = _array+_size-1;
    return *temp;
}

template <typename T>
void Vector<T>:: push_back(const T& item)
{
    _array = add_entry(_array, item, _size, _capacity);
}

template <typename T>
Vector<T>& Vector<T>:: operator +=(const T& item)
{
    _array = add_entry(_array, item, _size, _capacity);
    return *this;
}

template <typename T>
void Vector<T>::insert(int insert_here,const T& insert_this)
{
    // use add_entry to check if it needs reallocate
    _array = add_entry(_array, insert_this, _size, _capacity);
    shift_right_vector(_array, _size, insert_here);
    _array[insert_here]=insert_this;
}

template <typename T>
void Vector<T>::erase(int erase_index)
{
    shift_left_vector(_array, _size, erase_index);
    _array=remove_last(_array, _size, _capacity);
}

template <typename T>
int Vector<T>::index_of(const T& item)
{
    return find_position(item,_array,_size);
}

//size and capacity
template <typename T>
void Vector<T>::set_size(int size)
{
    _size = size;
}

template <typename T>
void Vector<T>::set_capacity(int capacity)
{
    _capacity = capacity;
}

template <typename T>
void Vector<T>:: pop_back()
{
    _array = remove_last(_array, _size, _capacity);
}

template <typename T>
bool Vector<T>::empty() const
{
    return size() < 1;
}

template <typename U>
ostream& operator << (ostream& outs, const Vector<U>& print_me)
{
    for(int i=0;i<print_me._size-1;i++)
        outs << print_me._array[i] << " ";
    outs << print_me._array[print_me._size-1];
    return outs;
}

#endif //TABLE_CLASS_VECTOR_H

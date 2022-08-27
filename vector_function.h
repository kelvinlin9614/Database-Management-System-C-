#ifndef TABLE_CLASS_VECTOR_FUNCTION_H
#define TABLE_CLASS_VECTOR_FUNCTION_H

#include <iostream>
#include <string>

using namespace std;

template <typename T>
void copy_list_vector(T *dest, T* src, int many_to_copy);

template <typename T>
T* allocate(int capacity);

template <typename T>
T* add_entry(T* list, const T& new_entry, int& size, int& capacity);

template <typename T>
void print (T* src, int size);

template <typename T>
void append(T* dest, int& size, T value);

template <typename T>
T *find(T src, T *dest, int dest_size);

template <typename T>
int find_position(T src, T *dest, int dest_size);

template <typename T>
void shift_left_vector(T* src, int &size, const T& delete_me);

template<typename T>
void shift_left_vector(T* src, int &size, int position);

template <typename T>
void shift_right_vector(T* src, int &size, int position);

template <typename T>
T* remove_entry(T* list, const T& delete_me, int& size, int& capacity);

template<typename T>
T* remove_last(T* list, int& size, int& capacity);

template <typename T>
T* allocate(int capacity)
{
    return new T[capacity];
}

// copy
template <typename T>
void copy_list_vector(T *dest, T* src, int many_to_copy)
{
    for (int i=0;i<many_to_copy;i++)
    {
        *dest=*src;
        dest++;
        src++;
    }
}

// add a new element to the end of the array
template <typename T>
T* add_entry(T* list, const T& new_entry, int& size, int& capacity)
{
    T*temp;
    if(size < capacity)
    {
        temp = list;
        append(temp,size,new_entry);
    }
    else
    {
        capacity=capacity*2;
        temp= allocate<T>(capacity);
        copy_list_vector(temp,list,size);
        delete[] list;
        append(temp,size,new_entry);
    }
    size++;
    return temp;
}

// remove an element and shift the rest of the elements to the left.
template<typename T>
T* remove_entry(T* list, const T& delete_me, int& size, int& capacity)
{
    T*temp;
    if(find(delete_me,list,size)== nullptr)
        temp=list;
    else
    {
        // the size reaches 1/4 of the capacity
        if(size <= capacity/4)
        {
            // reduce half of the capacity
            capacity = capacity/2;
            //Allocate the memory space for a new array
            temp = allocate<T>(capacity);
            //Copy the old array to the new array
            copy_list(temp,list,size);
            // delete the dynamic array
            delete [] list;
            //Shift elements after the repeated element to the left
            shift_left(temp,size,delete_me);
        }
        else
        {
            temp = list;
            shift_left(temp,size,delete_me);
        }
    }
    return temp;
}

template<typename T>
T* remove_last(T* list, int& size, int& capacity)
{
    T*temp;
    // check if the size reaches 1/4 of the capacity
    if(size <= capacity/4)
    {
        //Reduce half of the capacity
        capacity = capacity/2;
        //Allocate the memory space for a new array
        temp = allocate<T>(capacity);
        //Copy the old array to the new array
        copy_list_vector(temp,list,size-1);
        delete [] list;
    }
    else
    {
        temp = allocate<T>(capacity);
        copy_list_vector(temp,list,size-1);
    }
    size--;
    return temp;
}


// Shift elements after the repeated element to the left
template<typename T>
void shift_left_vector(T* src, int &size, const T& delete_me)
{
    for(T *i= find(delete_me,src,size); i< src+size-1;i++)
    {
        *i=*(i+1);
    }
    size--;
}

template<typename T>
void shift_left_vector(T* src, int &size, int position)
{
    for(int i=position;i<size-1;i++)
    {
        src[i]=src[i+1];
    }
}

template <typename T>
void shift_right_vector(T* src, int &size, int position)
{
    for(int i=size-1;i>=position ;i--)
    {
        src[i]=src[(i-1)];
    }
}

//This function appends a new element to the end of the array.
template<typename T>
void append(T* dest, int& size, T value)
{
    dest = dest + size;
    *dest = value;
}

template<typename T>
T* find(T src, T *dest, int dest_size)
{
    for(int i=0;i<dest_size;i++)
    {
        if(*dest == src)
        {
            //if found repeated element
            return dest;
        }

        else
            dest++;
    }
    //if not found, then return nullptr
    return nullptr;
}

template <typename T>
int find_position(T src, T *dest, int dest_size)
{
    int walker = 0;
    for (int i=0;i<dest_size;i++)
    {
        if (dest[i]==src)
            return walker;
        else
            walker++;
    }
    return -1;
}

// print an array by using its pointer.
template <typename T>
void print (T* src, int size)
{

    for (int i=0; i<size; i++)
    {
        cout << *src << " ";
        src++;
    }

    cout << endl << endl;
}

#endif //TABLE_CLASS_VECTOR_FUNCTION_H

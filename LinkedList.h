#ifndef TABLE_CLASS_LINKEDLIST_H
#define TABLE_CLASS_LINKEDLIST_H

#include <iostream>
#include <cassert>

using namespace std;
template <typename T>
struct node
{
    node<T>* _next;
    T _item;
    node(const T& i=T(), node<T>* n = NULL):_item(i), _next(n){}
    friend ostream& operator << (ostream& outs, const node<T>& print_me)
    {
        outs << "[" << print_me._item <<"] ->";
        return outs;
    }
};

template <class T>
node<T>* _search (node<T> *headptr,const T& item);

//initializes head to NULL
template <class T>
node<T>* init_head(node<T>* &head);

//deletes all the nodes in the list
template<class T>
void delete_all(node<T>*&head);

//true if head is NULL, false otherwise.
template <class T>
bool empty(const node<T>* head);

//makes a copy of the list, returns a pointer to the last node:
template <class T>
node<T>* copy_list(const node<T>* head, node<T>* & cpy);

//insert at the beginning of the list:
template <class T>
node<T>* insert_head(node<T>* &head, T item);

//insert_after: if after is NULL, inserts at head
template <class T>
node<T>* insert_after(node<T>* &head, node<T>* after, const T& item);

//delete the node at the head of the list, return the item:
template <class T>
T delete_head(node<T>* &head);

template <class T>
T _deleteNode(node<T>*&head, node<T>* deleteThis);

//print the list and return outs
template<class T>
ostream& print_list(const node<T>* head, ostream& outs=cout)
{
    while(head)
    {
        outs << "[" << head->_item << "]->";
        head = head->_next;
    }
    outs << "|||";
    return outs;
}

template <class T>
node<T>* _search (node<T> *headptr,const T& item)
{
    node<T>* walker = headptr;

    while (walker != nullptr)
    {
        if(walker->_item == item)
            return walker;

        else
            walker= walker->_next;
    }

    return nullptr;
    //assert(walker != nullptr);
}

//initializes head to NULL
template <class T>
node<T>* init_head(node<T>* &head)
{
    head = NULL;
    return head;
}

//deletes all the nodes in the list
template<class T>
void delete_all(node<T>*&head)
{
    assert(head);
    node<T>* walker = head;
    while(walker)
    {
        walker = walker->_next;
        delete_head(head);
    }
}

//true if head is NULL, false otherwise.
template <class T>
bool empty(const node<T>* head)
{
    if(!head)
        return true;
    else
        return false;
}

//makes a copy of the list, returns a pointer to the last node:
template <class T>
node<T>* copy_list(const node<T>* head, node<T>* & cpy)
{
    insert_head(cpy, head->_item);
    head = head->_next;
    node<T>* walker = cpy;
    while(head)
    {
        insert_after(cpy, walker, head->_item);
        head = head->_next;
        walker = walker->_next;
    }
    return walker;
}

//insert at the beginning of the list:
template <class T>
node<T>* insert_head(node<T>* &head, T item)
{
    node<T>* temp = new node<T>(item);
    temp->_next = head;
    head = temp;
    return head;
}

//insert_after: if after is NULL, inserts at head
template <class T>
node<T>* insert_after(node<T>* &head, node<T>* after, const T& item)
{
    if(after == NULL)
    {
        insert_head(after, item);
    }
    else{
        node<T> *temp = new node<T>(item);
        temp->_next = after->_next;
        after->_next = temp;
    }
    return head;
}

//delete the node at the head of the list, return the item:
template <class T>
T delete_head(node<T>* &head)
{
    assert(head);
    node<T>* temp = head;
    T item = head->_item;
    head = head->_next;
    delete(temp);
    return item;
}

template <class T>
T _deleteNode(node<T>*&head, node<T>* deleteThis)
{
    T hold = deleteThis->_item;
    node<T>* temp = _PreviousNode(head,deleteThis);

    if(head == deleteThis)      //if user wants to remove head
    {
        _remove_head(head);
        head == nullptr;
    }

    else
    {
        temp->_next=deleteThis->_next;
        delete deleteThis;
    }

    return hold;
}

#endif //TABLE_CLASS_LINKEDLIST_H

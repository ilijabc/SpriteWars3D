#ifndef BASENODE_H
#define BASENODE_H

#include <stdio.h>

template <class T>
class BaseNode
{
public:
    BaseNode();
    virtual ~BaseNode();

    T* add(T* node);
    void remove(T* node);
    void removeAll();
    T* getByIndex(int index);

    T* getNext() const { return next; }
    T* getPrev() const { return prev; }
    T* getFirst() const { return first; }
    T* getLast() const { return last; }
    T* getParent() const { return parent; }

private:
    T* next;
    T* prev;
    T* first;
    T* last;
    T* parent;
};


template <class T> BaseNode<T>::BaseNode()
{
    next = NULL;
    prev = NULL;
    first = NULL;
    last = NULL;
}

template <class T> BaseNode<T>::~BaseNode()
{
    removeAll();
}

template <class T> T* BaseNode<T>::add(T* node)
{
    if (first && last) //have children
    {
        last->next = node;
        node->prev = last;
        last = node;
        node->parent = (T*)this;
    }
    else //no children, add first
    {
        first = node;
        last = node;
        node->parent = (T*)this;
    }
    return node;
}

template <class T> void BaseNode<T>::remove(T* node)
{
    T* obj = first;
    while (obj)
    {
        if (obj == node)
        {
            if (obj == first && obj == last)
            {
                first = NULL;
                last = NULL;
            }
            else if (obj == first)
            {
                first = first->next;
            }
            else if (obj == last)
            {
                last = last->prev;
            }
            else
            {
                obj->prev->next = obj->next;
                obj->next->prev = obj->prev;
            }
            delete obj;
            return;
        }
        obj = obj->next;
    }
}

template <class T> void BaseNode<T>::removeAll()
{
    T* obj = first;
    while (obj)
    {
        T* obj_next = obj->next;
        delete obj;
        obj = obj_next;
    }
    first = NULL;
    last = NULL;
}

template <class T> T* BaseNode<T>::getByIndex(int index)
{
    T* obj = first;
    int i = 0;
    while (obj)
    {
        if (i == index)
            return obj;
        i++;
        obj = obj->next;
    }
    return NULL;
}

#endif // BASENODE_H

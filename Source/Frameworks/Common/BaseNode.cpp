#ifndef BASENODE_H
#define BASENODE_H


class BaseNode
{
public:
    BaseNode();
    virtual ~BaseNode();

    BaseNode* add(BaseNode* node);
    void remove(BaseNode* node);
    void removeAll();
    BaseNode* getByIndex(int index);

    inline BaseNode* getNext() const { return next; }
    inline BaseNode* getPrev() const { return prev; }
    inline BaseNode* getFirst() const { return first; }
    inline BaseNode* getLast() const { return last; }
    inline BaseNode* getParent() const { return parent; }

private:
    BaseNode* next;
    BaseNode* prev;
    BaseNode* first;
    BaseNode* last;
    BaseNode* parent;
};


#endif // BASENODE_H

#include "BaseNode.h"

#include <stdio.h>

BaseNode::BaseNode()
{
    next = NULL;
    prev = NULL;
    first = NULL;
    last = NULL;
}

BaseNode::~BaseNode()
{
    removeAll();
}

BaseNode* BaseNode::add(BaseNode* node)
{
    if (first && last) //have children
    {
        last->next = node;
        node->prev = last;
        last = node;
        node->parent = this;
    }
    else //no children, add first
    {
        first = node;
        last = node;
        node->parent = this;
    }
    return node;
}

void BaseNode::remove(BaseNode* node)
{
    BaseNode* obj = first;
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

void BaseNode::removeAll()
{
    BaseNode* obj = first;
    while (obj)
    {
        BaseNode* obj_next = obj->next;
        delete obj;
        obj = obj_next;
    }
    first = NULL;
    last = NULL;
}

BaseNode* BaseNode::getByIndex(int index)
{
    BaseNode* obj = first;
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

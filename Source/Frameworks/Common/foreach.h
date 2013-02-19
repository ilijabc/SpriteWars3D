#ifndef FOREACH_H
#define FOREACH_H


#include <list>
#include <vector>
#include <queue>
#include <stack>

/*
def:
    foreach (Type, Variable, List)
example:
    list<MyType> myList;
    ...
    foreach (MyType, item, myList)
    {
        cout << "value: " << item->myValue << endl;
        cout << "iterator: " << _i_item << endl;
    }
*/

#define foreach(T,I,L)  \
    T I = L.front(); \
    for(typeof( L.begin() )_##i##_##I=L.begin(); \
        _##i##_##I!=L.end(); \
        ++_##i##_##I, I=_##i##_##I!=L.end()?*_##i##_##I:I)

#define foreach_(I,L)  \
    I = L.front(); \
    for(typeof( L.begin() )_##i##_##I=L.begin(); \
        _##i##_##I!=L.end(); \
        ++_##i##_##I, I=_##i##_##I!=L.end()?*_##i##_##I:I)

//reverse

#define rforeach(T,I,L) \
    T I = L.back(); \
    for(typeof( L.rbegin() ) _##i##_##I=L.rbegin(); \
        _##i##_##I!=L.rend(); \
        ++_##i##_##I, I=_##i##_##I!=L.rend()?*_##i##_##I:I)

#define rforeach_(I,L) \
    I = L.back(); \
    for(typeof( L.rbegin() ) _##i##_##I=L.rbegin(); \
        _##i##_##I!=L.rend(); \
        ++_##i##_##I, I=_##i##_##I!=L.rend()?*_##i##_##I:I)

//utils

#define remove_item(I,L) _##i##_##I = --L.erase(_##i##_##I)

#define get_iterator(I) _##i##_##I

#endif // FOREACH_H




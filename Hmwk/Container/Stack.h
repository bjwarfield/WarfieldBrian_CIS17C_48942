/*
 * File: stack.h
 * Author: Brian Warfield
 * Class: CIS17-C C++: Data Structures
 * Purpose: Stack implementation
 */

#ifndef STACK_H
#define	STACK_H

#include "LinkedList.h"

template <class T>
class Stack{
public:
    Stack();
    Stack(T data);
    Stack(Stack& source);
    
    int size();
    void clear();
    void push(T data);
    T top();
    T pop();
    bool isEmpty();
    
    virtual ~Stack();

protected:
    LinkedList<T> list;
    
    
};



/**
 * Default Constructor
 */
template<class T>
Stack<T>::Stack()
{

}

/**
 *
 */
template<class T>
Stack<T>::Stack(T data)
{
    list.prepend(data);
}

/**
 *
 */
template<class T>
Stack<T>::Stack(Stack &source)
{
    list = source.list;
}

/**
 *
 */
template<class T>
int Stack<T>::size()
{
    return list.size();
}

template<class T>
void Stack<T>::clear()
{
    list.clearList();
}

/**
 *
 */
template<class T>
void Stack<T>::push(T data)
{
    list.prepend(data);
}

/**
 *
 */
template<class T>
T Stack<T>::top(){
    return list.first();
}

/**
 *
 */
template<class T>
T Stack<T>::pop(){
        return list.extract(0);

}

/**
 *
 */
template<class T>
bool Stack<T>::isEmpty()
{
    return list.isEmpty();
}

template<class T>
Stack<T>::~Stack()
{
    list.clearList();
}

#endif	/* STACK_H */



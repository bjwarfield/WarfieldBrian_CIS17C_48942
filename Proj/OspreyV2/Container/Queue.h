/*
 * File: Queue.h
 * Author: Brian Warfield
 * Class: CIS17-C C++: Data Structures
 * Purpose: Queue implementation
 */

#ifndef QUEUE_H
#define QUEUE_H

#include "DoubleLinkedList.h"


template<class T>
class Queue{
public:
    Queue();
    Queue(T data);
    Queue(Queue& source);

    int size();
    void clear();
    void pushBack(T data);
    T popFront();
    const T back();
    const T front();
    bool isEmpty();

    virtual ~Queue();

protected:
    DList<T> list;
};

/**
 *
 */
template<class T>
Queue<T>::Queue(){

}

/**
 *
 */
template<class T>
Queue<T>::Queue(T data){
     list.append(data);
}

/**
 *
 */
template<class T>
Queue<T>::Queue(Queue &source){
    list = source.list;
}

/**
 *
 */
template<class T>
int Queue<T>::size(){
    return list.size();
}

/**
 *
 */
template<class T>
void Queue<T>::clear(){
    list.clear();
}

/**
 *
 */
template<class T>
void Queue<T>::pushBack(T data){
    list.append(data);
}

/**
 *
 */
template<class T>
T Queue<T>::popFront(){
    return list.pullFront();
}

/**
 *
 */
template<class T>
T Queue<T>::back(){
    return list.last();
}

/**
 *
 */
template<class T>
T Queue<T>::front(){
    return list.first();
}

template<class T>
bool Queue<T>::isEmpty(){
    return list.isEmpty();
}

/**
 *
 */
template<class T>
Queue<T>::~Queue(){
    list.clear();
}

#endif // QUEUE_H

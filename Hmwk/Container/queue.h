#ifndef QUEUE
#define QUEUE

#include "DoubleLinkedList.h"

#endif // QUEUE
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
    T back();
    T front();
    bool isEmpty();

    virtual ~Queue();

protected:
    D_LinkedList<T> list;
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
    list.clearList();
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
    list.pullFront();
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
    list.clearList();
}

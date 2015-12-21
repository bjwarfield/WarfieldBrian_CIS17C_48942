#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H
#include "PriorityLinkedList.h"
#include "SortOrder.h"


template<class T>
class PriorityQueue:public SortOrder{
public:


    PriorityQueue(order type = ASC);
    PriorityQueue(T data, order type = ASC);
    PriorityQueue(PriorityQueue& source);

    int size();
    void clear();
    void push(T data);
    T pop();
    T front();
    T back();
    void printQueue();

    bool isEmpty();
    virtual ~PriorityQueue();



protected:
    order priority;
    P_LinkedList<T> list;
};

/**
 * @brief default constructor
 * @param ascending(default) or descending
 */
template<class T>
PriorityQueue<T>::PriorityQueue(order type):
    priority(type)
{

}

/**
 * @brief constructor with initial data
 * @param data initial data to insert
 * @param type ascending or descending order
 */
template<class T>
PriorityQueue<T>::PriorityQueue(T data, order type):
    priority(type)
{
    list.append(data);
}

/**
 * @brief constructor copying from existing priority queue
 * @param source priority queue from which to copy, same order type
 */
template<class T>
PriorityQueue<T>::PriorityQueue(PriorityQueue &source)
{
    list = source.list;
    priority = source.priority;
}

/**
 * @brief Priority queue size function
 * @return number of elementss stored in queue
 */
template<class T>
int PriorityQueue<T>::size()
{
    return list.size();
}

/**
 * @brief clear list of all contents
 */
template<class T>
void PriorityQueue<T>::clear()
{
    list.clearList();
}

/**
 * @brief add data to queue
 * @param data to be inserted
 */
template<class T>
void PriorityQueue<T>::push(T data)
{
    list.prepend(data);
}

/**
 * @brief removes and retuns highest priority data element
 * @return highest priority data element
 */
template<class T>
T PriorityQueue<T>::pop()
{
    if(priority == ASC){
        return list.popMin();
    }else{
        return list.popMax();
    }
}

/**
 * @brief view highest priority element in queue
 * @return highest priority element in queue
 */
template<class T>
T PriorityQueue<T>::front()
{
    if(priority == ASC){
        return list.peekMin();
    }else{
        return list.peekMax();
    }
}

/**
 * @brief view the lowest priority element in the queue
 * @return lowest priority element in queue
 */
template<class T>
T PriorityQueue<T>::back()
{
    if(priority == ASC){
        return list.peekMax();
    }else{
        return list.peekMin();
    }
}

/**
 * @brief output contents of queue to output stream
 */
template<class T>
void PriorityQueue<T>::printQueue()
{
    list.printList();
}

/**
 * @brief returns true if size od queue is 0
 * @return
 */
template<class T>
bool PriorityQueue<T>::isEmpty()
{
    return list.isEmpty();
}

template<class T>
PriorityQueue<T>::~PriorityQueue()
{
    list.clearList();
}


#endif // PRIORITYQUEUE_H



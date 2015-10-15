/* 
 * File:   linkedlist.h
 * Author: Bee-Jay
 *
 * Created on October 10, 2015, 12:14 AM
 */

#ifndef LINKEDLIST_H
#define	LINKEDLIST_H
#include <cstdlib>
#include <new>
#include <iostream>

using namespace std;

template<class T>
class LinkedList {
private:

    typedef struct node {
        T data;
        node *next = NULL;
    } * nodePtr;

    //marks the head of the linked list
    nodePtr head;
    //marks the active node in the list
    nodePtr current;
    //marks temporary node
    nodePtr temp;
    //tracks the size of the list
    unsigned int listSize;

    //handles subscript errors
    void subError();

public:
    //default constructor class
    LinkedList();
    //constructor initializes with one element
    LinkedList(T);
    //constructor initializes with a copy of the contents in the received list
//    LinkedList(LinkedList);


    //add data to new node
    void push(T newData);
    //remove last element and returns it
    T pull();
    //returns list size
    int size();

    //accessors to elements
    T get(int index);

    //overloaded [] operator declaration 
    T &operator[](const int &);

    //prints each element in order to output stream
    void printList();



    //destructor method. Deleted each allocated node in the list.
    ~LinkedList();

};

/*******************************************************************************
 * Default constructor class
 ******************************************************************************/
template<class T>
LinkedList<T>::LinkedList() {
    //no data, no nodes
    head = NULL;
    current = NULL;
    temp = NULL;
    listSize = 0;
}

/*******************************************************************************
 * subError, function. Displays an error message and terminates when a subscript
 * is out of range
 *******************************************************************************/
template<class T>
void LinkedList<T>::subError() {
    cout << "Error: subscript is out of range" << endl;
    exit(EXIT_FAILURE);
}

/*******************************************************************************
 * Constructor class. Initializes first node with data
 * @param data element to store
 ******************************************************************************/
template<class T>
LinkedList<T>::LinkedList(T addData) {
    //create new node
    temp = new node;
    temp->data = addData;
    temp->next = NULL;
    //set size counter
    listSize = 1;
    //set as new head to node
    current = head = temp;

}

/*******************************************************************************
 * Destructor function. Deleted all nodes
 *******************************************************************************/
template<class T>
LinkedList<T>::~LinkedList() {
    if (head) {
        current = head;
        while (current->next != NULL) {
            head = current;
            current = current->next;
            delete head;
        }
        delete current;

    }
}

/*******************************************************************************
 * Push function. Adds data in new node.
 * @param data to add to the list
 ******************************************************************************/
template<class T>
void LinkedList<T>::push(T newData) {
    //create new node
    temp = new node;
    temp->data = newData;
    temp->next = NULL;

    //if previous data exists
    if (head) {

        //traverse the list
        current = head;
        while (current->next != NULL) {
            current = current->next;
        }
        //append new node to end of list
        current->next = temp;
    } else {//if previous data does not exist
        //set new node as head
        head = temp;
    }

    listSize++;
}

/*******************************************************************************
 * get function. return element at selected index.
 * @param int index of element
*******************************************************************************/
template<class T>
T LinkedList<T>::get(int index){
    if(index < 0 || index >= static_cast<int>(listSize)){
        subError();
    }
    
    current = head;
    for(int i = 0; i < index; i++){
        current = current->next;
    }
    
    return current->data;
}

/*******************************************************************************
 * overloaded [] operator get function. return element at selected index.
 * @param int index of element
*******************************************************************************/
template<class T>
T &LinkedList<T>::operator [](const int &index){
    if(index < 0 || index >= static_cast<int>(listSize)){
        subError();
    }
    
    current = head;
    for(int i = 0; i < index; i++){
        current = current->next;
    }
    
    return current->data;
}

/*******************************************************************************
 * Pull function. removes data at end of list and returns it.
 * @return the removed element at the end of the list
 ******************************************************************************/
template<class T>
T LinkedList<T>::pull() {
    //locate head node 
    current = temp = head;

    //traverse to the end of the list
    while (current->next != NULL) {
        //remember previous node
        temp = current;
        current = current->next;
    }

    //capture data
    T pull = current->data;

    //if this is only node in the list
    if (current == head) {
        //delete node and set all to NULL
        delete head;
        head = current = temp = NULL;
    } else {
        //set previous nodePointer to NULL
        temp->next = NULL;
        //remove node
        delete current;
    }
    //decrement size counter
    listSize--;
    //return data
    return pull;
}

/*******************************************************************************
 * size function. returns the number of nodes in the list
 *******************************************************************************/
template<class T>
int LinkedList<T>::size() {
    return static_cast<int>(listSize);
}

/*******************************************************************************
 * Prints each element to a line in the output stream.
 *******************************************************************************/
template<class T>
void LinkedList<T>::printList() {
    if (head) {
        current = head;
        while (current != NULL) {
            cout << current->data << endl;
            ;
            current = current->next;
        }
    }
}
#endif	/* LINKEDLIST_H */


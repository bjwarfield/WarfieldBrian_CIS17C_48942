/*
 * File: LinkedList.h
 * Author: Brian Warfield
 * Class: CIS17-C C++: Data Structures
 * Purpose: linked list implementation
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
    //copy contents from list
    void copyList(LinkedList &);

public:
    //default constructor class
    LinkedList();
    //constructor initializes with one element
    LinkedList(T);
    //constructor initializes with a copy of the contents in the received list
    LinkedList(LinkedList &);


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

    //overloaded = operator declaration
    void operator=(LinkedList &);


    //return first element in list
    T first();

    //return last element in list
    T last();

    //add new element to beginning of list
    void prepend(T newData);

    //add new element to end of list
    void append(T newData);

    //prints each element in order to output stream
    void printList();

    //deletes contents of list
    void clearList();

    //extract by index
    T extract(int);

    void insertBefore(int index, T value);

    void insertAfter(int index, T value);

    bool isEmpty();


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
 * Copy constructor. Instantiates object with a copy of the values received in 
 * the provided linked list.
 ******************************************************************************/
template<class T>
LinkedList<T>::LinkedList(LinkedList &list) {
    head = NULL;
    current = NULL;
    temp = NULL;
    listSize = 0;
    copyList(list);
}

/*******************************************************************************
 * Copies contents from list parameter to current list
 * @param reference of list to be copied 
 ******************************************************************************/
template<class T>
void LinkedList<T>::copyList(LinkedList &list) {
    if (list.head) {
        temp = new node;
        temp->data = list.head->data;
        temp->next = NULL;

        head = temp;
        current = head;
        listSize++;

        list.current = list.head;

        for (int i = 1; i< static_cast<int> (list.listSize); i++) {
            list.current = list.current->next;

            temp = new node;
            temp->data = list.current->data;
            temp->next = NULL;

            current->next = temp;
            current = current->next;

            listSize++;
        }

    }

}

/*******************************************************************************
 * Deletes contents of list
 ******************************************************************************/
template<class T>
void LinkedList<T>::clearList() {
    if (head) {
        current = head;
        while (current->next != NULL) {
            head = current;
            current = current->next;
            delete head;
        }
        delete current;
        listSize = 0;
        temp = NULL;
        current = NULL;
        head = NULL;
    }
}

/*******************************************************************************
 * Destructor function. Deleted all nodes
 ******************************************************************************/
template<class T>
LinkedList<T>::~LinkedList() {
    clearList();
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
 ******************************************************************************/
template<class T>
T LinkedList<T>::get(int index) {
    if (index < 0 || index >= static_cast<int> (listSize)) {
        subError();
    }

    current = head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }

    return current->data;
}

/*******************************************************************************
 * overloaded [] operator get function. return element at selected index.
 * @param int index of element
 ******************************************************************************/
template<class T>
T &LinkedList<T>::operator[](const int &index) {
    if (index < 0 || index >= static_cast<int> (listSize)) {
        subError();
    }

    current = head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }


    return current->data;
}

/*******************************************************************************
 * Overloaded assignment operator. Clears content of list and creates a copy of 
 * the received list
 ******************************************************************************/
template<class T>
void LinkedList<T>::operator=(LinkedList& sourceList) {
    clearList();
    copyList(sourceList);
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
 * retrieve the first element in the list
 *******************************************************************************/
template<class T>
T LinkedList<T>::first() {
    if (!head) {
        subError();
    }
    return head->data;
}

/*******************************************************************************
 * retrieve the last element in the list
 *******************************************************************************/
template<class T>
T LinkedList<T>::last() {
    if (!head) {
        subError();
    }

    current = head;
    while (current->next != NULL) {
        current = current->next;
    }

    return current->data;
}

/*******************************************************************************
 * Add data to the beginning of the list
 *******************************************************************************/
template<class T>
void LinkedList<T>::prepend(T newData) {
    temp = new node;
    temp->data = newData;
    temp->next = head;

    head = temp;
    listSize++;
}

/*******************************************************************************
 * Add data to the end of the list
 ******************************************************************************/
template<class T>
void LinkedList<T>::append(T newData) {
    //create new node
    temp = new node;
    temp->data = newData;
    temp->next = NULL;

    //is list exists
    if (head) {
        current = head;
        while (current->next != NULL) {
            current = current->next;
        }
        //point tail to new node
        current->next = temp;
    } else {//if list does not exist
        //point head to new node
        head = temp;
    }
    //increment counter
    listSize++;
}

/*******************************************************************************
 * size function. returns the number of nodes in the list
 *******************************************************************************/
template<class T>
int LinkedList<T>::size() {
    //return listSize as int
    return static_cast<int> (listSize);
}

/*******************************************************************************
 * Prints each element to a line in the output stream.
 *******************************************************************************/
template<class T>
void LinkedList<T>::printList() {
    //if elements exist
    if (head) {
        current = head;
        //traverse the list and output elements
        while (current != NULL) {
            cout << current->data << endl;
            ;
            current = current->next;
        }
    }
}

template<class T>
T LinkedList<T>::extract(int index) {

    if (index < 0 || index >= static_cast<int> (listSize)) {
        subError();
    }

    T extracted;

    if (index == 0) {//first
        //get data
        extracted = head->data;
        //set current to old head
        current = head;
        //point head one up list
        head = head->next;
        //delete old head
        delete current;
        //decrement size counter
        listSize--;
        return extracted;
    } else if (index == static_cast<int> (listSize) - 1) {//last
        //set all pointers to head
        current = head;
        temp = current;
        //traverse list to index 
        for (int i = 0; i < index; i++) {
            temp = current; //remember previous
            current = current->next;
        }
        extracted = current->data; //get data
        temp->next = NULL; //set previous->next pointer to null
        delete current; //delete tail
        //decrement size counter
        listSize--;
        return extracted; //return data
    } else {//somewhere in the middle
        current = head; //point current to head
        temp = current;
        for (int i = 0; i < index; i++) {
            temp = current; //remember previous
            current = current->next;
        }
        extracted = current->data; //get data
        temp->next = current->next; //set previous->next pointer to current->next
        delete current; //delete middle node
        //decrement size counter
        listSize--;
        return extracted; //return data

    }

}

/*******************************************************************************
 * create new node and insert it before the provided index
 * @param int index
 * @param T value to be inserted
 ******************************************************************************/
template<class T>
void LinkedList<T>::insertBefore(int index, T value) {
    //subscript bound check
    if (index < 0 || index >= static_cast<int> (listSize)) {
        subError();
    }

    //set to head
    current = head;
    temp = current;
    if (index == 0) {//if first
        //create new node
        temp = new node;
        //set data
        temp->data = value;
        //set next pointer to head
        temp->next = head;
        //set head pointer to new first node
        head = temp;
        //increment list counter
        listSize++;
        return;
    } else {//if not first
        for (int i = 0; i < index; i++) {
            temp = current; //remember previous
            current = current->next; //traverse list
        }
        //create new node
        nodePtr newNode = new node;
        //capture data
        newNode->data = value;
        //point new->next to current
        newNode->next = current;
        //point previous->next to new
        temp->next = newNode;
        //increment listSize
        listSize++;
        return;
    }
}

/*******************************************************************************
 * create new node and insert it after the provided index
 * @param int index
 * @param T value to be inserted
 ******************************************************************************/
template<class T>
void LinkedList<T>::insertAfter(int index, T value) {

    //subscript bound check
    if (index < 0 || index >= static_cast<int> (listSize)) {
        subError();
    }

    //set to head
    current = head;
    //create new node
    temp = new node;
    //capture data
    temp->data = value;


    for (int i = 0; i < index; i++) {
        temp = current; //remember previous
        current = current->next; //traverse list
    }
    //point new->next to current->next
    temp->next = current->next;
    //point previous->next to new
    current->next = temp;
    //increment listSize
    listSize++;

}

/*******************************************************************************
 * @returns true is list is empty
 ******************************************************************************/
template<class T>
bool LinkedList<T>::isEmpty()
{
    return listSize == 0;
}
#endif	/* LINKEDLIST_H */


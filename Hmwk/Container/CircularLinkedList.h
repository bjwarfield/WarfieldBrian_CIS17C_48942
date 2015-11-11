/*
 * File: CircularLinkedList.h
 * Author: Brian Warfield
 * Class: CIS17-C C++: Data Structures
 * Purpose: circular linked list implementation
 */

#ifndef CIRCULARLINKEDLIST_H
#define	CIRCULARLINKEDLIST_H
#include <cstdlib>
#include <new>
#include <iostream>

using namespace std;

template<class T>
class C_LinkedList {
private:

    typedef struct node {
        T data;
        node *next = NULL;
    } * nodePtr;

    //marks the tail of the linked list
    nodePtr tail;
    //marks the active node in the list
    nodePtr current;
    //marks temporary node
    nodePtr temp;
    //tracks the size of the list
    unsigned int listSize;

    //handles subscript errors
    void subError();
    //copy contents from list
    void copyList(C_LinkedList &);

public:
    //default constructor class
    C_LinkedList();
    //constructor initializes with one element
    C_LinkedList(T);
    //constructor initializes with a copy of the contents in the received list
    C_LinkedList(C_LinkedList &);


    //add data to new node
    void push(T newData);
    //remove last element and returns it
    T pullBack();
    T pullFront();

    //returns list size
    int size();

    //accessors to elements
    T get(int index);

    //overloaded [] operator declaration
    T &operator[](const int &);

    //overloaded = operator declaration
    void operator=(C_LinkedList &);


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
    ~C_LinkedList();

};

/*******************************************************************************
 * Default constructor class
 ******************************************************************************/
template<class T>
C_LinkedList<T>::C_LinkedList() {
    //no data, no nodes
    tail = NULL;
    current = NULL;
    temp = NULL;
    listSize = 0;
}

/*******************************************************************************
 * subError, function. Displays an error message and terminates when a subscript
 * is out of range
 *******************************************************************************/
template<class T>
void C_LinkedList<T>::subError() {
    cout << "Error: subscript is out of range" << endl;
    exit(EXIT_FAILURE);
}

/*******************************************************************************
 * Constructor class. Initializes first node with data
 * @param data element to store
 ******************************************************************************/
template<class T>
C_LinkedList<T>::C_LinkedList(T addData) {
    //create new node
    temp = new node;
    temp->data = addData;
    temp->next = temp;
    //set size counter
    listSize = 1;
    //set as new head to node
    tail = temp;
    current = temp;

}

/*******************************************************************************
 * Copy constructor. Instantiates object with a copy of the values received in
 * the provided linked list.
 ******************************************************************************/
template<class T>
C_LinkedList<T>::C_LinkedList(C_LinkedList &list) {
    tail = NULL;
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
void C_LinkedList<T>::copyList(C_LinkedList &list) {
    if (list.tail) {
        temp = new node;
        temp->data = list.tail->data;
        temp->next = temp;

        tail = temp;
        current = temp;
        listSize++;

        list.current = list.tail;

        //        for (int i = 1; i< static_cast<int> (list.listSize); i++) {
        while (list.current->next != list.tail) {
            list.current = list.current->next;

            temp = new node;
            temp->data = list.current->data;
            temp->next = tail;

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
void C_LinkedList<T>::clearList() {
    if (tail) {
        current = tail;
        while (current->next != tail) {
            temp = current;
            current = current->next;
            delete temp;
        }
        delete current;
        listSize = 0;
        temp = NULL;
        current = NULL;
        tail = NULL;
    }
}

/*******************************************************************************
 * Destructor function. Deleted all nodes
 ******************************************************************************/
template<class T>
C_LinkedList<T>::~C_LinkedList() {
    clearList();
}

/*******************************************************************************
 * Push function. Adds data in new node.
 * @param data to add to the list
 ******************************************************************************/
//template<class T>
//void C_LinkedList<T>::push(T newData) {
//    //create new node
//    temp = new node;
//    temp->data = newData;


//    //if previous data exists
//    if (tail) {
//        temp->next= tail->next;

//        //traverse the list
//        current = tail;
////        while (current->next != head) {
////            current = current->next;
////        }
//        //append new node to end of list
//        current->next = temp;
//    } else {//if previous data does not exist
//        //set new node as head
//        temp->next = temp;
//        head = temp;
//    }

//    listSize++;
//}

/*******************************************************************************
 * get function. return element at selected index.
 * @param int index of element
 ******************************************************************************/
template<class T>
T C_LinkedList<T>::get(int index) {
    if (index < 0 || index >= static_cast<int> (listSize)) {
        subError();
    }

    current = tail->next;
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
T &C_LinkedList<T>::operator[](const int &index) {
    if (index < 0 || index >= static_cast<int> (listSize)) {
        subError();
    }

    current = tail->next;
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
void C_LinkedList<T>::operator=(C_LinkedList& sourceList) {
    clearList();
    copyList(sourceList);
}

/*******************************************************************************
 * Pull function. removes data at end of list and returns it.
 * @return the removed element at the end of the list
 ******************************************************************************/
template<class T>
T C_LinkedList<T>::pullBack() {
    //locate tail node
    current = tail;

    //traverse to the end of the list
    while (current->next != tail) {
        current = current->next;
    }

    //capture data
    T pull = tail->data;

    //if this is only node in the list
    if (current == tail) {
        //delete node and set all to NULL
        delete tail;
        tail = NULL;
        current = NULL;
        temp = NULL;
    } else {
        //set previous nodePointer to NULL
        current->next = tail->next;
        //remove node
        delete tail;

        tail=current;
    }
    //decrement size counter
    listSize--;
    //return data
    return pull;
}

/*******************************************************************************
 * PullFromt function. removes data at end of list and returns it.
 * @return the removed element at the end of the list
 ******************************************************************************/
template<class T>
T C_LinkedList<T>::pullFront() {
    //locate tail node
    current = tail->next;

    //capture data
    T pull = current->data;

    //if this is only node in the list
    if (current == tail) {
        //delete node and set all to NULL
        delete tail;
        tail = NULL;
        current = NULL;
        temp = NULL;
    } else {
        //set previous nodePointer to NULL
        tail->next = current->next;
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
T C_LinkedList<T>::first() {
    if (!tail) {
        subError();
    }
    return tail->next->data;
}

/*******************************************************************************
 * retrieve the last element in the list
 *******************************************************************************/
template<class T>
T C_LinkedList<T>::last() {
    if (!tail) {
        subError();
    }

    return tail->data;
}

/*******************************************************************************
 * Add data to the beginning of the list
 *******************************************************************************/
template<class T>
void C_LinkedList<T>::prepend(T newData) {
    temp = new node;
    temp->data = newData;

    if(tail){
        temp->next = tail->next;
        tail->next = temp;

    }else{
        temp->next = temp;
        tail = temp;
    }

    listSize++;
}

/*******************************************************************************
 * Add data to the end of the list
 ******************************************************************************/
template<class T>
void C_LinkedList<T>::append(T newData) {
    //create new node
    temp = new node;
    temp->data = newData;

    //is list exists
    if (tail) {
        temp->next = tail->next;
        tail->next = temp;
    } else {//if list does not exist
        temp->next = temp;
    }
    tail = temp;
    //increment counter
    listSize++;
}

/*******************************************************************************
 * size function. returns the number of nodes in the list
 *******************************************************************************/
template<class T>
int C_LinkedList<T>::size() {
    //return listSize as int
    return static_cast<int> (listSize);
}

/*******************************************************************************
 * Prints each element to a line in the output stream.
 *******************************************************************************/
template<class T>
void C_LinkedList<T>::printList() {
    //if elements exist
    if (tail) {
        current = tail->next;
        //traverse the list and output elements
        while (current->next != tail) {
            cout << current->data << endl;
            current = current->next;
        }
        cout<<tail->data<<endl;
    }
}

template<class T>
T C_LinkedList<T>::extract(int index) {

    if (index < 0 || index >= static_cast<int> (listSize)) {
        subError();
    }

    T extracted;

    if (index == 0) {//first
        current = tail->next;

        //get data
        extracted = current->data;

        tail->next = current->next;
        //delete old head
        delete current;
        //decrement size counter
        listSize--;
        if(listSize == 0){
            tail = NULL;
            current = NULL;
            temp = NULL;
        }
        return extracted;
    } else if (index == static_cast<int> (listSize) - 1) {//last
        extracted = tail->data;

        current = tail->next;
        //traverse list
        //        for (int i = 0; i < index; i++) {
        //            temp = current; //remember previous
        //            current = current->next;
        //        }
        while(current->next != tail){
            current = current->next;
        }
        current->next = tail->next;

        delete tail;
        tail = current;

        listSize--;
        return extracted; //return data
    } else {//somewhere in the middle
        current = tail->next; //point current to head
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
void C_LinkedList<T>::insertBefore(int index, T value) {
    //subscript bound check
    if (index < 0 || index >= static_cast<int> (listSize)) {
        subError();
    }

    //set to head
    current = tail->next;

    if (index == 0) {//if first
        //create new node
        temp = new node;
        //set data
        temp->data = value;
        //set next pointer to head
        temp->next = current;
        //set head pointer to new first node
        tail->next = temp;
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
void C_LinkedList<T>::insertAfter(int index, T value) {

    //subscript bound check
    if (index < 0 || index >= static_cast<int> (listSize)) {
        subError();
    }

    //set to head
    current = tail->next;

    //create new node
    temp = new node;
    //capture data
    temp->data = value;

    if(index == static_cast<int>(listSize)-1){//last element in list
        temp->next = tail->next;

        tail->next = temp;
        tail = tail->next;
    }else{//non-tail index
        for (int i = 0; i < index; i++) {
            current = current->next; //traverse list
        }

        //point new->next to current->next
        temp->next = current->next;
        //point current->next to new
        current->next = temp;
    }
    //increment listSize
    listSize++;

}

/*******************************************************************************
 * @returns true is list is empty
 ******************************************************************************/
template<class T>
bool C_LinkedList<T>::isEmpty()
{
    return listSize == 0;
}
#endif	/* CIRCULARLINKEDLIST_H */


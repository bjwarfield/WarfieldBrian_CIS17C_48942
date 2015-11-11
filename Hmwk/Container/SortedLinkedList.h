#ifndef SORTEDLINKEDLIST_H
#define SORTEDLINKEDLIST_H
#include <cstdlib>
#include <new>
#include <iostream>
#include "SortOrder.h"

using namespace std;

template<class T>
class S_LinkedList:public SortOrder {
protected:

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

    //determines ascending or decending sort order
    order sortOrder;

    //handles subscript errors
    void subError();
    //copy contents from list
    void copyList(S_LinkedList &);

public:
    //default constructor class
    S_LinkedList(order so = ASC);
    //constructor initializes with one element
    S_LinkedList(T, order so = ASC);
    //constructor initializes with a copy of the contents in the received list
    S_LinkedList(S_LinkedList &);


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
    void operator=(S_LinkedList &);


    //return first element in list
    T first();

    //return last element in list
    T last();

    //prints each element in order to output stream
    void printList();

    //deletes contents of list
    void clearList();

    //extract by index
    T extract(int);

    bool isEmpty();


    //destructor method. Deleted each allocated node in the list.
    virtual ~S_LinkedList();

};

/*******************************************************************************
 * Default constructor class
 ******************************************************************************/
template<class T>
S_LinkedList<T>::S_LinkedList(order so):sortOrder(so) {
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
void S_LinkedList<T>::subError() {
    cout << "Error: subscript is out of range" << endl;
    exit(EXIT_FAILURE);
}

/*******************************************************************************
 * Constructor class. Initializes first node with data
 * @param data element to store
 ******************************************************************************/
template<class T>
S_LinkedList<T>::S_LinkedList(T addData, order so):
sortOrder(so){
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
S_LinkedList<T>::S_LinkedList(S_LinkedList &list) {
    head = NULL;
    current = NULL;
    temp = NULL;
    listSize = 0;
    copyList(list);
    sortOrder = list.sortOrder;
}

/*******************************************************************************
 * Copies contents from list parameter to current list
 * @param reference of list to be copied
 ******************************************************************************/
template<class T>
void S_LinkedList<T>::copyList(S_LinkedList &list) {
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
void S_LinkedList<T>::clearList() {
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
S_LinkedList<T>::~S_LinkedList() {
    clearList();
}

/*******************************************************************************
 * Push function. Adds data in new node.
 * @param data to add to the list
 ******************************************************************************/
template<class T>
void S_LinkedList<T>::push(T newData) {
    //create new node
    temp = new node;
    temp->data = newData;


    //if previous data exists
     if (head) {
        current = head;//point to head
        //if (ascenting order and newData is less than or equal to head) or...
        if((sortOrder == ASC && newData <= head->data) ||
                //(decenting order and newData is breater than or equal to head)
                (sortOrder == DEC && newData >= head->data)){
            temp->next = head;//set new->next to head
            head = temp;//set head to new
        }else{
            while(current->next != NULL &&//if not end of list and...
                  //((ascending order and newData is greater than current) or...
                  ((sortOrder == ASC &&  newData > current->next->data) ||
                  //(decending order and newData is less than current))
                   (sortOrder == DEC &&  newData < current->next->data))){
                current = current->next;
            }//traverse list till end or current->next->data > new->data
            temp->next = current->next;//insert new before current->next
            current->next = temp;
        }

    } else {//if previous data does not exist
        temp->next = NULL;
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
T S_LinkedList<T>::get(int index) {
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
T &S_LinkedList<T>::operator[](const int &index) {
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
void S_LinkedList<T>::operator=(S_LinkedList& sourceList) {
    clearList();
    copyList(sourceList);
}

/*******************************************************************************
 * Pull function. removes data at end of list and returns it.
 * @return the removed element at the end of the list
 ******************************************************************************/
template<class T>
T S_LinkedList<T>::pull() {
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
T S_LinkedList<T>::first() {
    if (!head) {
        subError();
    }
    return head->data;
}

/*******************************************************************************
 * retrieve the last element in the list
 *******************************************************************************/
template<class T>
T S_LinkedList<T>::last() {
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
 * size function. returns the number of nodes in the list
 *******************************************************************************/
template<class T>
int S_LinkedList<T>::size() {
    //return listSize as int
    return static_cast<int> (listSize);
}

/*******************************************************************************
 * Prints each element to a line in the output stream.
 *******************************************************************************/
template<class T>
void S_LinkedList<T>::printList() {
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
T S_LinkedList<T>::extract(int index) {

    if (index < 0 || index >= static_cast<int> (listSize)) {
        subError();
    }

    T extracted;//to capture data

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
 * @returns true is list is empty
 ******************************************************************************/
template<class T>
bool S_LinkedList<T>::isEmpty()
{
    return listSize == 0;
}

#endif // SORTEDLINKEDLIST_H


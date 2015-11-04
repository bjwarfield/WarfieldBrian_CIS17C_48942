//doubly linked implementation

#ifndef DOUBLELINKEDLIST_H
#define	DOUBLELINKEDLIST_H
#include <cstdlib>
#include <new>
#include <iostream>

using namespace std;

template<class T>
class D_LinkedList {
private:

    typedef struct node {
        T data;
        node *next = NULL;
        node *prev = NULL;
    } * nodePtr;

    //marks the head of the linked list
    nodePtr head;
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
    void copyList(D_LinkedList &);

public:
    //default constructor class
    D_LinkedList();
    //constructor initializes with one element
    D_LinkedList(T);
    //constructor initializes with a copy of the contents in the received list
    D_LinkedList(D_LinkedList &);


    //remove first/last element and returns it
    T pullBack();
    T pullFront();

    //returns list size
    int size();

    //accessors to elements
    T get(int index);

    //overloaded [] operator declaration 
    T &operator[](const int &);

    //overloaded = operator declaration
    void operator=(D_LinkedList &);


    //return first element in list
    T first();

    //return last element in list
    T last();

    //add new element to beginning of list
    void prepend(T newData);

    //add new element to end of list
    void append(T newData);

    //prints each element in order to output stream
    void printForward();
    void printBackward();

    //deletes contents of list
    void clearList();

    //extract by index
    T extract(int);

    void insertBefore(int index, T value);
    void insertAfter(int index, T value);

    bool isEmpty();


    //destructor method. Deleted each allocated node in the list.
    ~D_LinkedList();

};

/*******************************************************************************
 * Default constructor class
 ******************************************************************************/
template<class T>
D_LinkedList<T>::D_LinkedList() {
    //no data, no nodes
    head = NULL;
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
void D_LinkedList<T>::subError() {
    cout << "Error: subscript is out of range" << endl;
    exit(EXIT_FAILURE);
}

/*******************************************************************************
 * Constructor class. Initializes first node with data
 * @param data element to store
 ******************************************************************************/
template<class T>
D_LinkedList<T>::D_LinkedList(T addData) {
    //create new node
    temp = new node;
    temp->data = addData;
    temp->next = NULL;
    temp->prev = NULL;
    //set size counter
    listSize = 1;
    //set as new head to node
    head = temp;
    tail = temp;
    current = temp;

}

/*******************************************************************************
 * Copy constructor. Instantiates object with a copy of the values received in 
 * the provided linked list.
 ******************************************************************************/
template<class T>
D_LinkedList<T>::D_LinkedList(D_LinkedList &list) {
    head = NULL;
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
void D_LinkedList<T>::copyList(D_LinkedList &list) {
    if (list.head) {
        temp = new node;
        temp->data = list.head->data;
        temp->next = NULL;
        temp->prev = NULL;

        head = temp;
        tail = temp;
        current = head;
        listSize++;

        list.current = list.head;

        for (int i = 1; i< static_cast<int> (list.listSize); i++) {
            list.current = list.current->next;

            temp = new node;
            temp->data = list.current->data;
            temp->next = NULL;
            temp->prev = current;

            current->next = temp;
            current = current->next;
            tail = current;

            listSize++;
        }

    }

}

/*******************************************************************************
 * Deletes contents of list
 ******************************************************************************/
template<class T>
void D_LinkedList<T>::clearList() {
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
        tail = NULL;
    }
}

/*******************************************************************************
 * Destructor function. Deleted all nodes
 ******************************************************************************/
template<class T>
D_LinkedList<T>::~D_LinkedList() {
    clearList();
}



/*******************************************************************************
 * get function. return element by value at selected index.
 * @param int index of element
 ******************************************************************************/
template<class T>
T D_LinkedList<T>::get(int index) {
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
 * overloaded [] operator get function. return element by reference at selected
 *  index.
 * @param int index of element
 ******************************************************************************/
template<class T>
T &D_LinkedList<T>::operator[](const int &index) {
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
void D_LinkedList<T>::operator=(D_LinkedList& sourceList) {
    clearList();
    copyList(sourceList);
}

/*******************************************************************************
 * PullBack function. removes data at end of list and returns it by value.
 * @return the removed element at the end of the list
 ******************************************************************************/
template<class T>
T D_LinkedList<T>::pullBack() {
    T pull = tail->data;
    current = tail->prev;
    current->next = NULL;
    delete tail;
    tail = current;
    listSize--;
    return pull;
}

/*******************************************************************************
 * PullFront function. removes data at end of list and returns it by value.
 * @return the removed element at the end of the list
 ******************************************************************************/
template<class T>
T D_LinkedList<T>::pullFront() {
    T pull = head->data;
    current = head->next;
    current->prev = NULL;
    delete head;
    head= current;
    listSize--;
    return pull;
}

/*******************************************************************************
 * retrieve the first element in the list
 *******************************************************************************/
template<class T>
T D_LinkedList<T>::first() {
    if (!head) {
        subError();
    }
    return head->data;
}

/*******************************************************************************
 * retrieve the last element in the list
 *******************************************************************************/
template<class T>
T D_LinkedList<T>::last() {
    if (!tail) {
        subError();
    }
    return tail->data;
}

/*******************************************************************************
 * Add data to the beginning of the list
 *******************************************************************************/
template<class T>
void D_LinkedList<T>::prepend(T newData) {
    temp = new node;
    temp->data = newData;
    temp->next = head;
    temp->prev = NULL;

    if(head){
        head->prev = temp;
        head = head->prev;
    }else{
        head = temp;
        tail = temp;
        current = temp;
    }
    listSize++;
}

/*******************************************************************************
 * Add data to the end of the list
 ******************************************************************************/
template<class T>
void D_LinkedList<T>::append(T newData) {
    //create new node
    temp = new node;
    temp->data = newData;
    temp->next = NULL;
    temp->prev = tail;

    if(tail){
        tail->next = temp;
        tail = tail->next;
        listSize++;
    }else{
        head = temp;
        tail = temp;
        current = temp;
    }
}

/*******************************************************************************
 * size function. returns the number of nodes in the list
 *******************************************************************************/
template<class T>
int D_LinkedList<T>::size() {
    //return listSize as int
    return static_cast<int> (listSize);
}

/*******************************************************************************
 * Prints each element from head to tail to a line in the output stream.
 *******************************************************************************/
template<class T>
void D_LinkedList<T>::printForward() {
    //if elements exist
    if (head) {
        current = head;
        //traverse the list and output elements
        while (current != NULL) {
            cout << current->data << endl;
            current = current->next;
        }
    }
}

template<class T>
void D_LinkedList<T>::printBackward(){
    if(tail){
        current = tail;
        while(current != NULL){
            cout << current->data << endl;
            current = current->prev;
        }
    }
}

template<class T>
T D_LinkedList<T>::extract(int index) {

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
        extracted = tail->data;
        current = tail;
        tail = tail->prev;
        delete current;
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
void D_LinkedList<T>::insertBefore(int index, T value) {
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
void D_LinkedList<T>::insertAfter(int index, T value) {

    //subscript bound check
    if (index < 0 || index >= static_cast<int> (listSize)) {
        subError();
    }

    //set to head
    current = head;


    for (int i = 0; i < index; i++) {
        current = current->next; //traverse list
    }
    //create new node
    temp = new node;
    //capture data
    temp->data = value;
    //point new->next to current
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
bool D_LinkedList<T>::isEmpty()
{
    return listSize == 0;
}
#endif	/* DOUBLELINKEDLIST_H */


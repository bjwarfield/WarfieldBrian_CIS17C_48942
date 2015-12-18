/*
 * File: DoubleLinkedList.h
 * Author: Brian Warfield
 * Class: CIS17-C C++: Data Structures
 * Purpose: doubly linked list implementation
 */

#ifndef DOUBLELINKEDLIST_H
#define	DOUBLELINKEDLIST_H
#include <cstdlib>
#include <new>
#include <iostream>

using namespace std;

template<class T>
class DList {
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

    //tracks the size of the list
    unsigned int listSize;

    //handles subscript errors
    void subError() const;
    //copy contents from list
    void copyList(const DList &);

    //hepler fundtion creates new nodePtr with attached data
    nodePtr createNode(const T &data);

public:
    //forward declaration
    class iterator;
    class const_iterator;

    //default constructor class
    DList();
    //constructor initializes with one element
    DList(T);
    //constructor initializes with a copy of the contents in the received list
    DList(DList &);


    //remove first/last element and returns it
    T pullBack();
    T pullFront();

    //returns list size
    int size() const;

    //accessors to elements
    T get(int index);
    T at(int index);

    //overloaded [] operator declaration 
    T &operator[](const int &);
    T &operator[](const int &)const;

    //overloaded = operator declaration
    void operator=(DList &);


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
    void clear();

    //extract by index
    T extract(int);
    T takeAt(int index);

    void insertBefore(int index, T value);
    void insert(int index, T value);
    void insertAfter(int index, T value);

    int indexOf(const T &value)const;

    void sort();

    bool isEmpty();


    //iterator begin
    iterator begin(){
        return iterator(head->next);
    }

    //iterator end
    iterator end(){
        return iterator(tail);
    }

    //iterator erase
    iterator &erase(iterator &it){
        if(listSize <1){
            subError();
        }

        nodePtr temp = it.current;

        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;

        it.current = temp->next;


        delete temp;
        listSize--;

        return it;
    }

    const const_iterator cbegin() const{
        return const_iterator(head->next);
    }

    //iterator end
    const const_iterator cend() const{
        return const_iterator(tail);
    }


    //destructor method. Deleted each allocated node in the list.
    ~DList();

    /**
     * nonconst iterarot inner class
     */
    friend class iterator;
    friend class const_iterator;
    class iterator{
        friend class DList;
    public:
        //default constructor
        iterator(){current = NULL;}
        //initialized constructor
        iterator(nodePtr n){ current = n; }
        //copy constructor
        iterator(const iterator &it):current(it.current){}
        //dereferece operator
        T &operator *() const{ return current->data; }
        //arrow operator
        T *operator ->() const{ return &current->data; }
        //equivilency operator
        bool operator ==(const iterator &it)const{ return current == it.current; }
        //inequivilency operator
        bool operator !=(const iterator &it)const{ return current != it.current; }
        //preincrement operator
        iterator &operator ++(){ current = current->next; return *this; }
        //postincrement operator
        iterator operator++(int){ nodePtr n = current; current = current->next; return n; }
        //predecrement operator
        iterator &operator --(){ current = current->prev; return *this; }
        //postdecrement operator
        iterator operator--(int){ nodePtr n = current; current = current->prev; return n; }

    private:
            nodePtr current;
    };

    class const_iterator{
        friend class DList;
    public:
        //default constructor
        const_iterator(){current = NULL;}
        //initialized constructor
        const_iterator(nodePtr n){ current = n; }
        //copy constructor
        const_iterator(const const_iterator &it){current = it.current;}
        //dereferece operator
        const T &operator *() const{ return current->data; }
        //arrow operator
        const T *operator ->() const{ return &current->data; }
        //equivilency operator
        bool operator ==(const const_iterator &it)const{ return current == it.current; }
        //inequivilency operator
        bool operator !=(const const_iterator &it)const{ return current != it.current; }
        //preincrement operator
        const const_iterator &operator ++(){ current = current->next; return *this; }
        //postincrement operator
        const const_iterator operator++(int){ nodePtr n = current; current = current->next; return n; }
        //predecrement operator
        const const_iterator &operator --(){ current = current->prev; return *this; }
        //postdecrement operator
        const const_iterator operator--(int){ nodePtr n = current; current = current->prev; return n; }

    private:
            nodePtr current;
    };
};

/*******************************************************************************
 * Default constructor class
 ******************************************************************************/
template<class T>
DList<T>::DList() {

    //create empty head and tail valid addresses
    head = new node;
    tail = new node;
    head->prev = NULL;
    head->next = tail;
    tail->prev = head;
    tail->next = NULL;

    listSize = 0;
}

/*******************************************************************************
 * subError, function. Displays an error message and terminates when a subscript
 * is out of range
 *******************************************************************************/
template<class T>
void DList<T>::subError() const {
    cout << "Error: subscript is out of range" << endl;
    exit(EXIT_FAILURE);
}

/*******************************************************************************
 * Constructor class. Initializes first node with data
 * @param data element to store
 ******************************************************************************/
template<class T>
DList<T>::DList(T addData) {
    //create new node
    nodePtr n = createNode(addData);


    head = new node;
    head->prev = NULL;
    head->next = n;



    tail = new node;
    tail->next = NULL;
    tail->prev = n;


    n->prev = head;
    n->next = tail;

    //set size counter
    listSize = 1;


}

/*******************************************************************************
 * Copy constructor. Instantiates object with a copy of the values received in 
 * the provided linked list.
 ******************************************************************************/
template<class T>
DList<T>::DList(DList &list) {
    head = new node;
    tail = new node;
    head->prev = NULL;
    head->next = tail;
    tail->prev = head;
    tail->next = NULL;

    listSize = 0;
    copyList(list);
}

/*******************************************************************************
 * Copies contents from list parameter to current list
 * @param reference of list to be copied 
 ******************************************************************************/
template<class T>
void DList<T>::copyList(const DList &list) {
    if (list.size() > 0) {
        nodePtr current = head;
        nodePtr listCurrent = list.head;

        for (int i = 0; i < list.size(); i++) {
            //traverse sourceList
            listCurrent = listCurrent->next;

            //copy sourceList node Data
            nodePtr temp = createNode(listCurrent->data);
            //connect new node traversal pointers
            temp->prev = current;
            temp->next = current->next;

            //connect next and prev nodes  treversal pointers
            current->next = temp;
            temp->next->prev = temp;

            //traverse current list
            current = current->next;

            //increment size
            listSize++;
        }

    }

}

/*******************************************************************************
 * Helper function created new node with given data.
 * @param data with which to fill new node
 ******************************************************************************/
template<class T>
typename DList<T>::nodePtr DList<T>::createNode(const T &data)
{
    nodePtr n = new node;
    n->data = data;
    n->next = NULL;
    n->prev = NULL;

    return n;
}

/*******************************************************************************
 * Deletes contents of list
 ******************************************************************************/
template<class T>
void DList<T>::clear() {
    if (listSize > 0) {
        nodePtr current = head->next;
        while (current != tail) {
            head->next = current->next;
            current->next->prev = head;
            delete current;
            current = head->next;
        }
        listSize = 0;
    }
}

/*******************************************************************************
 * Destructor function. Deleted all nodes
 ******************************************************************************/
template<class T>
DList<T>::~DList() {
    clear();
    delete head;
    delete tail;
}



/*******************************************************************************
 * get function. return element by value at selected index.
 * @param int index of element
 ******************************************************************************/
template<class T>
T DList<T>::get(int index) {
    if (index < 0 || index >= size() ) {
        subError();
    }

    nodePtr current = head->next;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }

    return current->data;
}

/*******************************************************************************
 *get function. return element by value at selected index.
 * @param int index of element
 ******************************************************************************/
template<class T>
T DList<T>::at(int index)
{
    return get(index);
}

/*******************************************************************************
 * overloaded [] operator get function. return element by reference at selected
 *  index.
 * @param int index of element
 ******************************************************************************/
template<class T>
T &DList<T>::operator[](const int &index) {
    if (index < 0 || index >= size() ) { subError(); }

    nodePtr current = head->next;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }


    return current->data;
}

template<class T>
T &DList<T>::operator[](const int &index) const
{
    if (index < 0 || index >= size() ) {
        subError();
    }

    nodePtr current = head->next;
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
void DList<T>::operator=(DList& sourceList) {
    clear();
    copyList(sourceList);
}

/*******************************************************************************
 * PullBack function. removes data at end of list and returns it by value.
 * @return the removed element at the end of the list
 ******************************************************************************/
template<class T>
T DList<T>::pullBack() {

    if(listSize ==0){
        subError();
    }

    T pull = tail->prev->data;
    nodePtr current = tail->prev;

    current->prev->next = tail;
    tail->prev = current-> prev;
    delete current;

//    current->next = NULL;
//    delete tail;
//    tail = current;

    listSize--;
    return pull;
}

/*******************************************************************************
 * PullFront function. removes data at end of list and returns it by value.
 * @return the removed element at the end of the list
 ******************************************************************************/
template<class T>
T DList<T>::pullFront() {
    T pull = head->next->data;

    nodePtr current = head->next;

    head->next = current->next;
    current->next->prev = head;
    delete current;

//    current->prev = NULL;
//    delete head;
//    head= current;

    listSize--;
    return pull;
}

/*******************************************************************************
 * retrieve the first element in the list
 *******************************************************************************/
template<class T>
T DList<T>::first() {
    if (listSize < 1) {
        subError();
    }
    return head->next->data;
}

/*******************************************************************************
 * retrieve the last element in the list
 *******************************************************************************/
template<class T>
T DList<T>::last() {
    if (listSize < 1) {
        subError();
    }
    return tail->prev->data;
}

/*******************************************************************************
 * Add data to the beginning of the list
 *******************************************************************************/
template<class T>
void DList<T>::prepend(T newData) {
    nodePtr temp = createNode(newData);
//    temp->data = newData;
//    temp->next = head;
//    temp->prev = NULL;

    temp->prev = head;
    temp->next = head->next;

    head->next = temp;
    temp->next->prev = temp;

    listSize++;
}

/*******************************************************************************
 * Add data to the end of the list
 ******************************************************************************/
template<class T>
void DList<T>::append(T newData) {
    //create new node
    nodePtr temp = createNode(newData);

    temp->next = tail;
    temp->prev = tail->prev;

    tail->prev = temp;
    temp->prev->next = temp;

    listSize++;
}

/*******************************************************************************
 * size function. returns the number of nodes in the list
 *******************************************************************************/
template<class T>
int DList<T>::size() const{
    //return listSize as int
    return static_cast<int> (listSize);
}

/*******************************************************************************
 * Prints each element from head to tail to a line in the output stream.
 *******************************************************************************/
template<class T>
void DList<T>::printForward() {
    //if elements exist
    if (listSize > 0) {
        nodePtr current = head->next;
        //traverse the list and output elements
        while (current != tail) {
            cout << current->data << endl;
            current = current->next;
        }
    }else{
        cout<<"List is Empty\n";
    }
}

template<class T>
void DList<T>::printBackward(){
    if(listSize > 0){
        nodePtr current = tail->prev;
        while(current != head){
            cout << current->data << endl;
            current = current->prev;
        }
    }else{
        cout<<"List is Empty\n";
    }
}

template<class T>
T DList<T>::extract(int index) {

    if (index < 0 || index >= size() ) {
        subError();
    }

    T extracted;
    //traverse to index
    nodePtr current = head->next;
    for (int i = 0; i < index; ++i) {
        current = current->next;
    }
    //get data
    extracted = current->data;

    //connect prev and next to each other
    current->prev->next = current->next;
    current->next->prev = current->prev;

    //disconnect current
    current->next = NULL;
    current->prev = NULL;
    //delete node
    delete current;
    //decriment size
    listSize--;
    //return data
    return extracted;

}

template<class T>
T DList<T>::takeAt(int index)
{
    return extract(index);
}

/*******************************************************************************
 * create new node and insert it before the provided index
 * @param int index
 * @param T value to be inserted
 ******************************************************************************/
template<class T>
void DList<T>::insertBefore(int index, T value) {
    //subscript bound check
    if (index < 0 || index > size()) {
        subError();
    }


    nodePtr current = head->next;
    for (int i = 0; i < index; ++i) {
        current = current->next;
    }

    nodePtr n = createNode(value);

    n->next = current;
    n->prev = current->prev;

    current->prev = n;
    n->prev->next = n;

    listSize++;
}

/**
 *same as insert before
 */
template<class T>
void DList<T>::insert(int index, T value)
{
    insertBefore(index, value);
}

/*******************************************************************************
 * create new node and insert it after the provided index
 * @param int index
 * @param T value to be inserted
 ******************************************************************************/
template<class T>
void DList<T>::insertAfter(int index, T value) {

    //subscript bound check
    if (index < 0 || index >= size()) {
        subError();
    }

    nodePtr current = head->next;
    for (int i = 0; i < index; ++i) {
        current = current->next;
    }

    nodePtr n = createNode(value);

    n->prev = current;
    n->next = current->next;

    current->next = n;
    n->next->prev = n;

    listSize++;

}

/*******************************************************************************
 * Returns first index mating given value. -1 of not found
 * @param value for which to search
 * @return first index matching value. -1 if not found;
 ******************************************************************************/
template<class T>
int DList<T>::indexOf(const T &value) const
{
    int count = 0;

    nodePtr current = head->next;

    while(current != tail){
        if(current->data == value){
            return count;
        }
        current = current->next;
        count++;
    }
    return -1;
}

/*******************************************************************************
 * sort function using bubblesort algorithm
 ******************************************************************************/
template<class T>
void DList<T>::sort()
{
    bool swapped;
    T tempData;
    for (int i = 0; i < size(); ++i) {//for each element in list
        swapped = false;//set flag
        nodePtr current = head->next;//start at first node;
        for (int j = 1; j < size() - i; ++j) {
            //for each node minus nodes bubbled to the top
            if(current->data > current->next->data){
                //if current data is greater then next data, swap data
                tempData = current->next->data;
                current->next->data = current->data;
                current->data = tempData;
                swapped = true;//set flag
            }

            current = current->next;//traverse list
        }
        if(!swapped){//break loop if no nodes were swapped in inner loop
            break;
        }
    }
}

/*******************************************************************************
 * @returns true is list is empty
 ******************************************************************************/
template<class T>
bool DList<T>::isEmpty()
{
    return listSize == 0;
}




#endif	/* DOUBLELINKEDLIST_H */


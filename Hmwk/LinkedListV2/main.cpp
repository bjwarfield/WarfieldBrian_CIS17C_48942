/*
 * File:   main.cpp
 * Author: Bee-Jay
 *
 * Created on October 13, 2015, 4:10 PM
 */
#include <iostream>
#include "linkedlist.h"

int main(int argc, char **argv) {
    LinkedList<int> list;

    for (int i = 10; i <= 15; i++) {
        list.push(i);
    }

    cout << "First element in the List:\t" << list.first() << endl;
    cout << "Last element in the List:\t" << list.last() << endl;

    //add element to beginning
    list.prepend(50);
    cout << "First element in the List:\t" << list.first() << endl;

    list.append(100);
    cout << "Last element in the List:\t" << list.last() << endl;

    cout << "Creating newList the the values of the old list" << endl;
    LinkedList<int> newList(list);

    newList.printList();

    newList[0] = 5;
    cout << "First element in the newList:\t" << newList.first() << endl;


    list = newList;
    list.printList();

    //test address space
    for (int i = 0; i < list.size(); i++) {
        cout << "list[" << i << "] \tValue:" << list[i] << "  \t@Address: " << &list[i] << endl;
        cout << "newlist[" << i << "]\tValue:" << newList[i] << "  \t@Address: " << &newList[i] << endl;
    }

    //testing extract functionality
    cout << "List size: " << list.size() << endl;
    cout << "Extracting value: " << list.extract(0) << endl;
    cout << "List size: " << list.size() << endl;
    cout << "Extracting value: " << list.extract(list.size()-1) << endl;
    cout << "List size: " << list.size() << endl;
    cout << "Extracting value: " << list.extract(3) << endl;
    cout << "List size: " << list.size() << endl;
    list.printList();
    
    //adding values
    for(int i = 0; i<5;i++){
        list.push(5);
    }
    cout << "List size: " << list.size() << endl;
    list.printList();
    
    
    
}

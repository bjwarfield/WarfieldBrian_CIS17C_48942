/*
 * File:   main.cpp
 * Author: Bee-Jay
 *
 * Created on October 10, 2015, 12:09 AM
 */
#include <iostream>
#include "linkedlist.h"

using namespace std;

int main(int argc, char **argv) {

    //create object
    LinkedList<int> list; 
    
    //populate list
    for(int i = 10; i < 19; i++){
        list.push(i);
    }
    
    //retrieve from index
    cout<< list.get(3)<<endl;
    
    //retrieve using subscript operator
    cout << list[1]<<endl;
    
    //output size
    cout << "List size: "<< list.size()<<endl;

    //pull(remove and output) last three value
    cout << list.pull()<< endl;
    cout << list.pull()<< endl;
    cout << list.pull()<< endl;

    //output size
    cout << "List size: "<< list.size()<<endl;

    //output list
    list.printList();
    
    //output list alternative
    for (int i = 0; i<list.size(); i++){
        cout<< "Element at index "<<i<<":\t"<<list.get(i)<<endl;
    }
    
}

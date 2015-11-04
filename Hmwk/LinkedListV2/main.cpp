
#include <iostream>
#include "linkedlist.h"

int main(int argc, char **argv) {
    LinkedList<int> list;

    cout << "Pushing 6 values 10 thru 15\n";
    for (int i = 10; i <= 15; i++) {
        list.push(i);
    }

    cout << "First element in the List:\t" << list.first() << endl;
    cout << "Last element in the List:\t" << list.last() << endl;
    cout << "List size: " << list.size() << endl;
    cout << "\n\n";

    //add element to beginning
    cout << "Prepending 50\n";
    list.prepend(50);
    cout << "First element in the List:\t" << list.first() << endl;
    cout << "List size: " << list.size() << endl;

    cout << "Appending 100\n";
    list.append(100);
    cout << "Last element in the List:\t" << list.last() << endl;
    cout << "List size: " << list.size() << endl;
    cout << "\n\n";

    //copy constructor
    cout << "Creating newList with the values of the old list using copy constructor" << endl;
    LinkedList<int> newList(list);
    cout << "Outputting new list\n";
    newList.printList();
    cout << "List size: " << newList.size() << endl;

    cout << "Testing subscript operator[]. Setting newList[0] to 5\n";
    newList[0] = 5;
    cout << "First element in the newList:\t" << newList.first() << endl;
    cout << "Testing subscript operator[]. Setting newList[5] to 777\n";
    newList[5] = 777;
    cout << "Element in newList[5]: " << newList[5] << endl;
    
    cout << "\n\n";


    cout << "Testing assignment operator=. Assigning list to the values of newList.\n";
    cout << "list before assignment:\n";
    list.printList();
    
    list = newList;
    cout << "list after assignment:\n";
    list.printList();

    cout << "\n\n";
    
    //test address space
    cout << "Testing for address space\n";
    for (int i = 0; i < list.size(); i++) {
        cout << "list[" << i << "] \tValue:" << list[i] << "  \t@Address: " << &list[i] << endl;
        cout << "newlist[" << i << "]\tValue:" << newList[i] << "  \t@Address: " << &newList[i] << endl;
    }
    cout << "\n\n";
    
    //testing extract functionality
    cout << "List size: " << list.size() << endl;
    cout << "Extracting value at list[0](first): " << list.extract(0) << endl;
    cout << "List size: " << list.size() << endl;
    cout << "Extracting value at list[n-1](last): " << list.extract(list.size() - 1) << endl;
    cout << "List size: " << list.size() << endl;
    cout << "Extracting value at list[3](middle): " << list.extract(3) << endl;
    cout << "List size: " << list.size() << endl;
    cout << "Outputting List\n";
    list.printList();
    cout << "\n\n";
    
    //adding values
    cout << "Inserting value 20 before list[0](first)\n";
    list.insertBefore(0,20);
    cout << "Outputting List\n";
    list.printList();
    cout << "\n";
    
    cout << "Inserting value 50 before list[3](middle)\n";
    list.insertBefore(3,50);
    cout << "Outputting List\n";
    list.printList();
    cout << "\n";
    
    cout << "Inserting value 200 before list[6](last)\n";
    list.insertBefore(6,200);
    cout << "Outputting List\n";
    list.printList();
    cout << "\n\n";

    return 0;

}

/*
 * File: main.h
 * Author: Brian Warfield
 * Class: CIS17-C C++: Data Structures
 * Purpose: test various container implementations
 */

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Stack.h"
#include "CircularLinkedList.h"
#include "Queue.h"
#include "DoubleLinkedList.h"
#include "PriorityLinkedList.h"
#include "priorityqueue.h"
#include "SortedLinkedList.h"

using namespace std;

int main()
{

    srand(time(0));
    /*
    cout<<"Creating new doubly linked list\n";
    D_LinkedList<int> dll(10);
    cout<<"Outputting list\n";
    dll.printForward();
    cout<<"\n\n";

    cout<<"Appending Values\n";
    for (int var = 10; var < 20; ++var) {
        dll.append(var+1);
    }

    cout<<"Outputting list with list Size: "<<dll.size()<<endl;
    dll.printForward();
    cout<<"\n\n";

    cout<<"Prepending Values\n";
    for (int var = 10; var > 0; --var) {
        dll.prepend(var-1);
    }

    cout<<"Outputting list with list Size: "<<dll.size()<<endl;
    dll.printForward();
    cout<<"\n\n";
    cout<<"Outputting list in reverse order with list Size: "<<dll.size()<<endl;
    dll.printBackward();
    cout<<"\n\n";

    cout<<"First: "<<dll.first()<<endl;
    cout<<"Last: "<<dll.last()<<endl;
    cout<<"\n\n";

    cout<<"Pulling First: "<<dll.pullFront()<<endl;
    cout<<"Pulling Last: "<<dll.pullBack()<<endl;
    cout<<"Outputting list with list Size: "<<dll.size()<<endl;
    dll.printForward();
    cout<<"\n\n";

    cout<<"Inserting value 100 after\n";
    dll.insertAfter(9,100);
    cout<<"Outputting list with list Size: "<<dll.size()<<endl;
    dll.printForward();
    cout<<"\n\n";

    cout<<"Inserting value 50 before\n";
    dll.insertBefore(9,50);
    cout<<"Outputting list with list Size: "<<dll.size()<<endl;
    dll.printForward();
    cout<<"\n\n";

    cout<<"Testing operator[] \n";
    dll[9]=75;
    cout<<dll.get(9)<<endl;
    cout<<"\n\n";

    cout<<"Testing Extract\n";
    cout<<dll.extract(9)<<endl;
    cout<<"Outputting list with list Size: "<<dll.size()<<endl;
    dll.printForward();
    cout<<"\n\n";

*/

    /*
    cout<<"\n****************************************************************\n";
    cout<<"Creating new circular linked list\n";
    C_LinkedList<int> cll(10);
    cout<<"Outputting list\n";
    cll.printList();
    cout<<"\n\n";

    cout<<"Appending Values\n";
    for (int var = 10; var < 20; ++var) {
        cll.append(var+1);
    }

    cout<<"Outputting list with list Size: "<<cll.size()<<endl;
    cll.printList();
    cout<<"\n\n";

    cout<<"Prepending Values\n";
    for (int var = 10; var > 0; --var) {
        cll.prepend(var-1);
    }
    cout<<"Outputting list with list Size: "<<cll.size()<<endl;
    cll.printList();
    cout<<"\n\n";

    cout<<"First: "<<cll.first()<<endl;
    cout<<"Last: "<<cll.last()<<endl;
    cout<<"\n\n";

    cout<<"Pulling First: "<<cll.pullFront()<<endl;
    cout<<"Pulling Last: "<<cll.pullBack()<<endl;
    cout<<"Outputting list with list Size: "<<cll.size()<<endl;
    cll.printList();
    cout<<"\n\n";

    cout<<"Inserting value 100 after\n";
    cll.insertAfter(9,100);
    cout<<"Outputting list with list Size: "<<cll.size()<<endl;
    cll.printList();
    cout<<"\n\n";

    cout<<"Inserting value 50 before\n";
    cll.insertBefore(9,50);
    cout<<"Outputting list with list Size: "<<cll.size()<<endl;
    cll.printList();
    cout<<"\n\n";

    cout<<"Testing operator[] \n";
    cll[9]=75;
    cout<<cll.get(9)<<endl;
    cout<<"\n\n";

    cout<<"Testing Extract\n";
    cout<<cll.extract(9)<<endl;
    cout<<"Outputting list with list Size: "<<cll.size()<<endl;
    cll.printList();
    cout<<"\n\n";

*/


/*
    Stack<int> stack(0);

    cout << "Populating Stack"<<endl;

    for (int var = 0; var < 10; ++var) {
        stack.push(var+1);
    }

    cout<<"Stack Size: "<<stack.size()<<endl;

    cout<<"\n\n";
    cout<<"Testing top() and pop() functions\n";
    cout<<stack.top()<<endl;
    stack.pop();
    cout<<stack.pop()<<endl;
    cout<<"\n\n";

    cout<<"testing copy construcor\n";
    Stack<int> newStack(stack);
    cout<<"stack top(): "<<stack.top()<<endl;
    cout<<"stack size(): "<<stack.size()<<endl;
    cout<<"newStack top(): "<<newStack.top()<<endl;
    cout<<"newStack size(): "<<newStack.size()<<endl;
    cout<<"\n\n";
*/

//    cout<<"Clearing newStack\n";
//    newStack.clear();
//    cout<<"stack size(): "<<stack.size()<<endl;
//    cout<<"stack top(): "<<stack.top()<<endl;
//    cout<<"newStack size(): "<<newStack.size()<<endl;//outputs 0
//    cout<<"newStack top(): "<<newStack.top()<<endl;//causes subscript error
//    cout<<"\n\n";

    /*
    Queue<int> queue(0);

    cout << "Populating queue"<<endl;

    for (int var = 0; var < 10; ++var) {
        queue.pushBack(var+1);
    }

    cout<<"Queue Size: "<<queue.size()<<endl;

    cout<<"\n\n";
    cout<<"Testing front() and back() functions\n";
    cout<<queue.front()<<endl;
    cout<<queue.back()<<endl;
    cout<<"\n\n";

    cout<<"Testing PopFront() function\n";
    cout<<queue.popFront()<<endl;
    cout<<"Queue Size: "<<queue.size()<<endl;
    cout<<"\n\n";

    cout<<"testing copy construcor\n";
    Queue<int> newQueue(queue);
    cout<<"queue front(): "<<queue.front()<<endl;
    cout<<"queue size(): "<<queue.size()<<endl;
    cout<<"newQueue front(): "<<newQueue.front()<<endl;
    cout<<"newQueue size(): "<<newQueue.size()<<endl;
    cout<<"\n\n";

    cout<<"Popping Valued from newQueue\n";
    for (int i = 0; i < 5; ++i) {
        cout<<newQueue.popFront()<<endl;
    }
    cout<<"queue front(): "<<queue.front()<<endl;
    cout<<"queue size(): "<<queue.size()<<endl;
    cout<<"newQueue front(): "<<newQueue.front()<<endl;
    cout<<"newQueue size(): "<<newQueue.size()<<endl;
    cout<<"\n\n";
*/

    /*
    cout<<"***********************************\nTesting Priority Linked List\n";

    P_LinkedList<int> pll;

    for (int i = 0; i < 20; ++i) {
        pll.append(i+1);
    }

    cout<<"Outputting list of size: "<<pll.size()<<endl;
    pll.printList();
    cout<<"\n\n";

    cout<<"Outputting peekMax()\n";
    cout<<pll.peekMax()<<endl;
    cout<<"Outputting popMax()\n";
    cout<<pll.popMax()<<endl;
     cout<<"Outputting list of size: "<<pll.size()<<endl;
     pll.printList();
     cout<<"\n\n";

     cout<<"Outputting peekMin()\n";
     cout<<pll.peekMin()<<endl;
     cout<<"Outputting popMin()\n";
     cout<<pll.popMin()<<endl;
     cout<<"Outputting list of size: "<<pll.size()<<endl;
     pll.printList();
     cout<<"\n\n";
     */

    /*
    cout<<"*****************************************\nTesting Priority Queue\n";

    PriorityQueue<int> pq;

    for (int i = 0; i < 20; ++i) {
        pq.push((rand()%30)+1);
    }

    cout<<"Outputting list of size: "<<pq.size()<<endl;
    pq.printQueue();
    cout<<"\n\n";

    cout<<"OutPutting front()\n";
    cout<< pq.front()   <<endl;
    cout<<"OutPutting back()\n";
    cout<< pq.back()   <<endl;
    cout<<"\n\n";


    cout<<"pop()ing 10 elements\n";
    for (int i = 0; i < 10; ++i) {
        cout<<pq.pop()<<endl;
    }
    cout<<"\n\n";

    cout<<"Outputting list of size: "<<pq.size()<<endl;
    pq.printQueue();
    cout<<"\n\n";

    cout<<"Instanciating descending object\n";
    PriorityQueue<int> pqd(sortOrder::DEC);

    for (int i = 0; i < 10; ++i) {
        pqd.push((rand()%15)+1);
    }
    cout<<"Outputting list of size: "<<pqd.size()<<endl;
    pqd.printQueue();
    cout<<"\n\n";

    cout<<"OutPutting front()\n";
    cout<< pqd.front()   <<endl;
    cout<<"OutPutting back()\n";
    cout<< pqd.back()   <<endl;
    cout<<"\n\n";


    cout<<"pop()ing 5 elements\n";
    for (int i = 0; i < 5; ++i) {
        cout<<pqd.pop()<<endl;
    }
    cout<<"\n\n";

    cout<<"Outputting list of size: "<<pqd.size()<<endl;
    pqd.printQueue();
    cout<<"\n\n";
    */

    cout<<"*************************************\nTesting Sorted Linked List\n";
    S_LinkedList<int> sll(SortOrder::ASC);

    for (int i = 0; i < 100; ++i) {
        sll.push((rand()%50)+1);
    }

    cout<<"Outputting lis of size: "<<sll.size()<<endl;
    sll.printList();
    cout<<"\n\n";

    return 0;
}


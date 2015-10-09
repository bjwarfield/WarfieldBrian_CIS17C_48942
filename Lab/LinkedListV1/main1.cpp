/* 
 * File:   main.cpp
 * Author: Dr. Mark E. Lehr
 * Created on September 18, 2014, 1:55 PM
 * Purpose:  Explore creation of a linked list class Version 1
 */

//System Libraries
#include <cstdlib>
#include <iostream>
using namespace std;

//Structure and Function prototype
struct Node{
    int data;
    Node *next;
};

int main(int argc, char** argv) {
    //Create a pointer for the front of the list and
    //a worker node
    Node *head,*worker;
    //Create 3 chain link nodes
    Node *clink1=new Node;
    Node *clink2=new Node;
    Node *clink3=new Node;
    //Fill them with data and hook them together
    head=clink1;
    clink1->data=1;
    clink1->next=clink2;
    clink2->data=2;
    clink2->next=clink3;
    clink3->data=3;
    clink3->next=NULL;
    //Traverse and print the data
    worker=head;
    cout<<"First data element in the list ->"<<worker->data<<endl;
    worker=worker->next;
    cout<<"Second data element in the list ->"<<worker->data<<endl;
    worker=worker->next;
    cout<<"Third data element in the list ->"<<worker->data<<endl;
    worker=worker->next;
    cout<<"Where are we pointing?"<<worker<<endl;
    //Now we have to destroy the Nodes before we leave
    worker=head;
    worker=worker->next;
    delete head;
    head=worker;
    worker=worker->next;
    delete head;
    head=worker;
    worker=worker->next;
    delete head;
    //Exit stage right!
    return 0;
}
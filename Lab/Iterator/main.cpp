#include <iostream>
#include <cstdlib>
#include <ctime>

#include "DoubleLinkedList.h"
using namespace std;

int main()
{
    srand(time(0));
    cout<<"Creating new doubly linked list\n";
        DList<int> dll(10);
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

        cout<<"Testing Copy Constructor\n";
        DList<int> dll2(dll);
        cout<<"Outputting list\n";
        dll2.printForward();
        cout<<"\n\n";


        cout<<"Testing iterator inner class\n";
        DList<int>::iterator it;
        for(it = dll2.begin(); it != dll2.end(); it++){
            cout<< *it <<endl;
        }
        cout<<"\n\n";


//        cout<<"Testing ClearList\n";
//        dll.clearList();
//        cout<<"Outputting list with list Size: "<<dll.size()<<endl;
//        dll.printForward();
//        cout<<"\n\n";


    return 0;
}


#include <iostream>
#include <cstdlib>
#include <ctime>
#include "simplevector.h"
using namespace std;

int main()
{
    Vector<int> vector;//reallocation occurs at 2^n increments

//    cout << "Element at 0: " << vector.getElementAt(0)<<endl<<endl;

    //populate vector with random values
    srand(time(0));
    
    for (int count = 0; count <10; count++){
//        vector.push(rand()%100);
        vector.push_back(count);
    }
    
    //pushing additional value should double allocation
    cout<<endl<<"Pushing random value"<<endl;
    vector.push_back(rand()%100);
    cout << vector[10] << endl;
    
    //testing operator[] override
    cout<<endl<<"altering value 10 usingn [] operator"<<endl;
    vector[10] = 9999;
    
    cout << vector[10] << endl;
    //pulling values from end should reduce array utilization to less than half
    //triggering reallocation
    
    cout<<endl<<"Pulling values from back.."<<endl;
    cout<<vector.pop_back()<<endl;
    cout<<vector.pop_back()<<endl;
    cout<<vector.pop_back()<<endl;
    cout <<"\n\n";
    cout<<endl<<"Pulling values from front.."<<endl;
    cout<<vector.pop_front()<<endl;
    cout<<vector.pop_front()<<endl;
    //
    //output contents


    //testing iterator
    cout<<"testing iterator functionality\n";
    Vector<int>::iterator it;

    for(it = vector.begin(); it != vector.end(); it++){
        cout<<*it<<endl;
    }
    cout <<"\n\n";

    //output size and maxSize
    cout<<"Vector Size: "<<vector.size()<<"  \tVector Max Size: "<<vector.capacity()<<endl;
    
    cout <<"\n\n";
    cout<<"Resizing Vector to 12\n";
    vector.resize(17);
    for(it = vector.begin(); it != vector.end(); it++){
        cout<<*it<<endl;
    }
    cout<<"Vector Size: "<<vector.size()<<"  \tVector Max Size: "<<vector.capacity()<<endl;
    cout <<"\n\n";

    //new vector
    cout << "Creating new vector with size of 10\n";
    Vector<int> vector2(10);

    for (int i = 0; i < vector2.size(); ++i) {
        vector2[i] = i;
    }

    for(it = vector2.begin(); it != vector2.end(); it++){
        cout<<*it<<endl;
    }
    cout<<" Vector Size: "<<vector2.size()<<"  \tVector Max Size: "<<vector2.capacity()<<endl;
    cout <<"\n\n";

    cout << "Inserting value 20 at index 5\n";
    vector2.insert(5,20);
    cout << "Prepending value 100\n";
    vector2.prepend(100);
    cout << "Appending value 50\n";
    vector2.append(50);
    for(it = vector2.begin(); it != vector2.end(); it++){
        cout<<*it<<endl;
    }
    cout<<" Vector Size: "<<vector2.size()<<"  \tVector Max Size: "<<vector2.capacity()<<endl;
    cout <<"\n\n";
    return 0;
}


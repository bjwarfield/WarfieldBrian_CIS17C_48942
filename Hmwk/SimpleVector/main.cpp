#include <iostream>
#include <cstdlib>
#include <ctime>
#include "simplevector.h"
using namespace std;

int main()
{
    SimpleVector<int> vector;//reallocatioin occurs at 2^n increments

//    cout << "Element at 0: " << vector.getElementAt(0)<<endl<<endl;

//    //populate vector with random values
    srand(time(0));
    
    for (int count = 0; count <1024; count++){
//        vector.push(rand()%100);
        vector.push(count);
    }
    
    //pushing additional value should double allocation 
    cout<<endl<<"Pushing random value"<<endl;
    vector.push(rand()%100);
    
    
    vector[1024] = 9999;
    
    cout << vector[1024] << endl;
    //pulling values from end should reduce array utilization to less than half
    //triggering reallocation
    
    cout<<endl<<"Pulling values.."<<endl;
    cout<<vector.pull()<<endl;
    cout<<vector.pull()<<endl;
    cout<<vector.pull()<<endl;
    cout<<vector.pull()<<endl;
    cout<<vector.pull()<<endl;
    
    //output contents
//    for(int i = 0; i < vector.size(); i++){
//        cout << "Element at "<< i<<": " << vector.getElementAt(i)<<endl;
//    }

    //output size and maxSize
    cout<<endl<<"Vector Size: "<<vector.size()<<"  \tVector Max Size: "<<vector.maxSize()<<endl;
    

    return 0;
}


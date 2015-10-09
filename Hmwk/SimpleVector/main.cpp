#include <iostream>
#include <cstdlib>
#include <ctime>
#include "simplevector.h"
using namespace std;

int main()
{
    SimpleVector<int> vector;

//    cout << "Element at 0: " << vector.getElementAt(0)<<endl<<endl;



    //populate vector with random vales
    srand(time(0));
    for (int count = 0; count <2.56e2; count++){
        vector.push(rand()%100);
    }

    vector.push(rand()%100);
    vector.push(rand()%100);
    cout << vector.pull()<<endl;
    cout << vector.pull()<<endl;
    cout << vector.pull()<<endl;
    cout << vector.pull()<<endl;
    cout << vector.pull()<<endl;

    //output contents
//    for(int i = 0; i < vector.size(); i++){
//        cout << "Element at "<< i<<": " << vector.getElementAt(i)<<endl;
//    }

    //output size and maxSize
    //cout<<endl<<"Vector Size: "<<vector.size()<<"  \tVector Max Size: "<<vector.getMaxSize()<<endl;
    return 0;
}


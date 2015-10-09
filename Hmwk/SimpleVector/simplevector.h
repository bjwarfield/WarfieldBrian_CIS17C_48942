#ifndef SIMPLEVECTOR_H
#define SIMPLEVECTOR_H

#include <iostream>
#include <new> //needed for bad alloc
#include <cstdlib> //neded for exit function

using namespace std;

template <class T>
class SimpleVector
{
private:
    T* arrayPtr;            //To point to the allocated array
    unsigned int arraySize;      //number of elements in the array
    unsigned int allocSize;        //maximum number of elements
    void memError();    //handles memory allocation errors
    void subError();    //handles subscripts out of range
    void sizeError();   //handles copyto size limits error

public:
    //default constructor
    SimpleVector();

    //constructor declaration
    SimpleVector(unsigned int s);

    //copy constructor declaration
    SimpleVector(const SimpleVector &);

    //destructor declaration
    ~SimpleVector();

    //accessor to the arraySize
    int size()const {return arraySize;}

    //accessor the allocSize
    int maxSize()const {return allocSize;}

    //acessor to the specific element if the vector
    T getElementAt (unsigned int posistion);

    //overloaded [] operator declaration
    T &operator[](const unsigned int &);

    //push routine
    void push(T item);

    //pull routine
    T pull();
};


/*
 * Default constructor for SimpleVector class
 * sets pointer and arraySize to zero
*/
template<class T>
SimpleVector<T>::SimpleVector(){
    arrayPtr = 0;
    arraySize = 0;
    allocSize = 0;
}

/*
* Constructor for SimpleVector class.
* Sets the size of the array and allocates
* memory for it.
*/

template<class T>
SimpleVector<T>::SimpleVector(unsigned int s)
{
    //set the array size
    arraySize = s;

    //set the size for memory to be allocated
    allocSize = 1;

    //double allocSize until it is greater than array size
    while(allocSize<s){
        allocSize*=2;
    }

    //for debugging
    cout<< "allocating size for "<<allocSize<<" elements"<<endl;

    //allocate memory for the array
    try {
        arrayPtr = new T[allocSize];
    }catch(bad_alloc){
        memError();
    }

    //initialize the array
    for (unsigned int count = 0; count <arraySize; count++){
        *(arrayPtr + count)=0;
    }
}

/*
 * Copy constructor for simple vector class
*/
template<class T>
SimpleVector<T>::SimpleVector(const SimpleVector &obj){
    //copy the array size and maxSize
    arraySize = obj.arraySize;
    allocSize = obj.allocSize;


    //allocate memory for the array
    cout<< "allocating size for "<<allocSize<<" elements"<<endl;
    try{
        arrayPtr = new T[allocSize];
    }catch(bad_alloc){
        memError();
    }


    //copy contents of obj to current current instance
    for(unsigned int i = 0; i < arraySize(); i++){
        arrayPtr[i] = obj.arrayPtr[i];
    }

}



/*
* Destructor for simpleVector Class
*/

template<class T>
SimpleVector<T>::~SimpleVector()
{
    if(arraySize>0)
        delete arrayPtr;
}

/*
 * memError function. Displays an error message and
 * terminates the memory allocation fails
*/
template<class T>
void SimpleVector<T>::memError(){
    cout << "ERROR: Cannot allocate memory. /n";
    exit(EXIT_FAILURE);
}

/*
 * subError function. Displays an error message and
 * terminates when a subscript is out of range
*/
template<class T>
void SimpleVector<T>::subError(){
    cout << "ERROR: subscript is out of range. /n";
    exit(EXIT_FAILURE);
}

/* sizeError function. Displays error message and
 * terminates when the destination vector is of
 * insufficient size to recieve source vectors
 * sontents
*/
template<class T>
void SimpleVector<T>::sizeError(){
    cout << "ERROR: Destinion vector too small to recieve"
            "contents of source. /n";
    exit(EXIT_FAILURE);
}

/*
 * getElementAt function. The argument is a subscript.
 * This function returns the value stored at the sub-script
 * in the array
 */
template<class T>
T SimpleVector<T>::getElementAt(unsigned int position){
    if(position < 0 || position >= arraySize){
        subError();
    }
    return arrayPtr[position];
}

/*
 * Overloaded [] operator. The argument is a subscript.
 * This function returns a reference to the element
 * in the array
 */
template<class T>
T &SimpleVector<T>::operator[](const unsigned int &posistion)
{
    getElementAt(posistion);
}

/*
 * push function. push element to the end of the vector.
 * double at the top to gold the new value pushed
 */
template<class T>
void SimpleVector<T>::push(T item)
{
    if(arraySize+1 > allocSize){// if adding a new element exceeds max size
        //calculate new allocSize
        unsigned int newMax = 1;
        while(newMax < arraySize+1){
            newMax*=2;
        }

        //allocate the appropriate memory
        T *newArray;
        try{
            cout<< "allocating size for "<<newMax<<" elements"<<endl;
            newArray = new T[newMax];
        }catch(bad_alloc){
            memError();
        }

        //copy values to newArray
        for(unsigned int i=0; i<arraySize;i++){
            newArray[i] = arrayPtr[i];
        }

        //add new item
        newArray[arraySize] = item;
        
        //delete old array
        delete arrayPtr;
        //set old array to point to new array
        arrayPtr = newArray;
        //set new allocSize
        allocSize = newMax;
        //increase arraySize by 1
        arraySize++;
    }else{//no new allocation needed for new value
        //assign next key to new value
        arrayPtr[arraySize]=item;
        //increment arraysize to account
        arraySize++;
    }
}

/*
 * pull function. removes last item in array and reduces array size by one.
 * If arraySize is less than half of capacity, cut capacity in half. Returns
 * removed item.
 */
template<class T>
T SimpleVector<T>::pull()
{
    //capture value of last entry
    T temp = arrayPtr[arraySize];

    //if removing last entry sets array utilization to less than half
    if(arraySize-1 < allocSize/2){
        //decriment arraySize
        arraySize--;

        //allocate new array with half the size of current
        T *smaller;
        cout<< "allocating size for "<<allocSize/2<<" elements"<<endl;
        try{
            smaller = new T[allocSize/2];
        }catch(bad_alloc){
            memError();
        }

        //copy contents to new array
        for(unsigned int i=0; i<arraySize; i++){
            smaller[i] = arrayPtr[i];
        }

        //delete old array
        delete arrayPtr;
        //point to new array
        arrayPtr = smaller;

        //set new allocSize
        allocSize /=2;


    }else{//if removing last entry doe NOT set array utilization to less than half
        //decriment array
        arraySize--;

    }
    //return removed element
    return temp;
}



#endif // SIMPLEVECTOR_H
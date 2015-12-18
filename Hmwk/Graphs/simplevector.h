#ifndef SIMPLEVECTOR_H
#define SIMPLEVECTOR_H

#include <iostream>  //for output strea
#include <QDebug>
#include <new>       //needed for bad alloc
#include <cstdlib>   //neded for exit function

using namespace std;

template <class T>
class Vector
{
private:
    T* arrayPtr;                //To point to the allocated array
    unsigned int arraySize;     //number of elements in the array
    unsigned int allocSize;     //maximum number of elements
    void memError()const;            //handles memory allocation errors
    void subError()const;            //handles subscripts out of range

public:
    //iterator implementation
    typedef T* iterator;
    typedef const T* const_iterator;

    iterator begin(iterator = iterator()){return arrayPtr;}
    iterator end(iterator = iterator()) {return arrayPtr + size(); }
    const_iterator begin(const_iterator = const_iterator())const{return arrayPtr;}
    const_iterator end(const_iterator = const_iterator())const{return arrayPtr + size();}
    const_iterator constBegin(const_iterator = const_iterator())const{return arrayPtr;}
    const_iterator constEnd(const_iterator = const_iterator())const{return arrayPtr + size();}

    //default constructor
    Vector();

    //constructor declaration
    Vector(unsigned int s);

    //copy constructor declaration
    Vector(const Vector &);

    //destructor declaration
    ~Vector();

    //accessors to the arraySize
    int size()const {return arraySize;}

    //accessors the allocSize
    int capacity()const {return allocSize;}

    //accessors to the value of the specific element of the vector
    T &at (int posistion)const;

    //overloaded [] operator declaration. Returns element by reference
    T &operator[](const int &);

    //push routine
    void push_back(const T &item);
    void push_front(const T &item);

    //pop routine
    T pop_back();
    T pop_front();


    T *data();

    int indexOf(const T &value, int from=0)const;
    int lastIndexOf(const T &value, int from=-1)const;
    bool contains(const T &value)const;
    int count(const T &value)const;
    void append(const T &value);
    void prepend(const T &value);
    void replace(int index, const T &value);
    T takeAt(int index);
    void insert(int index, const T &value);
    void resize(unsigned int newSize);
    T first()const { return *arrayPtr; }
    T last()const { return *(arrayPtr + arraySize-1);}
    bool isEmpty();
    void clear();





};


/*******************************************************************************
 * Default constructor for SimpleVector class sets pointer and arraySize to zero
*******************************************************************************/
template<class T>
Vector<T>::Vector(){
    arrayPtr = 0;
    arraySize = 0;
    allocSize = 0;
}

/*******************************************************************************
* Constructor for SimpleVector class.Sets the size of the array and allocates
* memory for it.
*******************************************************************************/
template<class T>
Vector<T>::Vector(unsigned int s)
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
//    cout<< "Debug msg: Allocating size for "<<allocSize<<" elements"<<endl;

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

/*******************************************************************************
 * Copy constructor for simple vector class
*******************************************************************************/
template<class T>
Vector<T>::Vector(const Vector &obj){
    //copy the array size and maxSize
    arraySize = obj.arraySize;
    allocSize = obj.allocSize;


    //allocate memory for the array
//    cout<< "allocating size for "<<allocSize<<" elements"<<endl;
    try{
        arrayPtr = new T[allocSize];
    }catch(bad_alloc){
        memError();
    }


    //copy contents of obj to current current instance
    for(unsigned int i = 0; i < arraySize; i++){
        arrayPtr[i] = obj.arrayPtr[i];
    }

}



/*******************************************************************************
* Destructor for simpleVector Class
*******************************************************************************/

template<class T>
Vector<T>::~Vector()
{
    if(arrayPtr)
        delete arrayPtr;
}

/*******************************************************************************
 * memError function. Displays an error message and terminates the memory
 * allocation fails
*******************************************************************************/
template<class T>
void Vector<T>::memError() const{
    qDebug() << "ERROR: Cannot allocate memory. /n";
    exit(EXIT_FAILURE);
}

/*******************************************************************************
 * subError function. Displays an error message and terminates when a subscript
 * is out of range
*******************************************************************************/
template<class T>
void Vector<T>::subError() const{
    qDebug() << "ERROR: subscript is out of range. /n";
    exit(EXIT_FAILURE);
}


/*******************************************************************************
 * getElementAt function. The argument is a subscript. This function returns
 * the value stored at the sub-script in the array
 ******************************************************************************/
template<class T>
T &Vector<T>::at(int position) const{
    if(position < 0 || position >= static_cast<int>(arraySize)){
        subError();
    }
    return arrayPtr[position];
}

/*******************************************************************************
 * Overloaded [] operator. The argument is a subscript. This function returns
 * a reference to the element in the array
 ******************************************************************************/
template<class T>
T &Vector<T>::operator[](const int &position)
{
    if(position < 0 || position >= static_cast<int>(arraySize)){
        subError();
    }
    return arrayPtr[position];
}

/*******************************************************************************
 * push_back function. push element to the end of the vector. Double at the top to
 * hold the new value pushed
 ******************************************************************************/
template<class T>
void Vector<T>::push_back(const T &item)
{
    if(arraySize+1 > allocSize){// if adding a new element exceeds max size
        //calculate new allocSize
        int newMax = 1;
        while(newMax < size()+1){
            newMax*=2;
        }

        //allocate the appropriate memory
        T *newArray;
        try{
            newArray = new T[newMax];
        }catch(bad_alloc){
            memError();
        }

        //copy values to newArray
        for( int i=0; i<size();i++){
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
        //increment arraySize to account
        arraySize++;
    }
}

/**
 * push_back function. push element to the begining of the vector. Double at
 * the top to hold the new value pushed
 * @param item
 */
template<class T>
void Vector<T>::push_front(const T &item)
{
    if(arraySize+1 > allocSize){// if adding a new element exceeds max size
        //calculate new allocSize
        int newMax = 1;
        while(newMax < size()+1){
            newMax*=2;
        }

        //allocate the appropriate memory
        T *newArray;
        try{
            newArray = new T[newMax];
        }catch(bad_alloc){
            memError();
        }

        //add new item
        newArray[0] = item;

        //copy values to newArray
        for( int i=0; i<size();i++){
            newArray[i+1] = arrayPtr[i];
        }

        //delete old array
        delete arrayPtr;
        //set old array to point to new array
        arrayPtr = newArray;
        //set new allocSize
        allocSize = newMax;
        //increase arraySize by 1
        arraySize++;
    }else{//no new allocation needed for new value
        for (int i = size(); i > 0; --i) {
            arrayPtr[i] = arrayPtr[i-1];
        }
        //assign next key to new value
        arrayPtr[0]=item;
        //increment arraySize to account
        arraySize++;
    }
}

/*******************************************************************************
 * pop_back function. removes last item in array and reduces array size by one.
 * Returns removed item.
 ******************************************************************************/
template<class T>
T Vector<T>::pop_back()
{
    //capture value of last entry
    T temp = arrayPtr[arraySize-1];
    arraySize--;

    //return removed element
    return temp;
}

/*******************************************************************************
 * pop_front function. removes first item in array and reduces array size by one.
 * Returns removed item.
 ******************************************************************************/
template<class T>
T Vector<T>::pop_front()
{
    //capture value of last entry
    T temp = arrayPtr[0];
    for(int i = 0; i< size()-1; i++){
        arrayPtr[i] = arrayPtr[i+1];
    }
    arraySize--;

    //return removed element
    return temp;
}

/*******************************************************************************
 * Returns a pointer to the data stored in the vector. The pointer can be used
 *  to access and modify the items in the vector
 * @return Template object array
 ******************************************************************************/
template<class T>
T *Vector<T>::data()
{
    return arrayPtr;
}

/*******************************************************************************
 * Returns the index position of the first occurrence of value in the vector,
 *  searching forward from index position from. Returns -1 if no item matched.
 * @param value for which to search
 * @param from starting index
 * @return first index matching from from given start. -1 if not found
 ******************************************************************************/
template<class T>
int Vector<T>::indexOf(const T &value, int from) const
{

    if(from < 0){
        from = qMax(from + size(), 0);
    }
    if(from < size()){

        for (int i = from; i < size(); ++i) {
            if(arrayPtr[i] == value){
                return i;
            }
        }
    }
    return -1;
}
/*******************************************************************************
 * Returns the index position of the last occurrence of value in the vector,
 *  searching bascwards from index position from. Returns -1 if no item matched.
 * @param value for which to search
 * @param from starting index
 * @return last index matching from from given start. -1 if not found
 ******************************************************************************/
template<class T>
int Vector<T>::lastIndexOf(const T &value, int from) const
{
    if(from< 0){
        from += size();
    }else if(from >= size()){
        from = size()-1;
    }
    if(from >= 0){
        for(int i  = from; i <=0; --i){
            if(arrayPtr[i] == value){
                return i;
            }
        }
    }
    return -1;
}

/*******************************************************************************
 * Returns true if the vector contains an occurrence of value; otherwise returns false
 * @param value to search for
 * @return true if found, false if not
 ******************************************************************************/
template<class T>
bool Vector<T>::contains(const T &value) const
{
    return indexOf(value)>= 0 ? true : false;
}

/******************************************************************************
 * Returns the number of occurrences of value in the vector
 * @param value to count
 * @return number of occurrences of value in the vector
 *****************************************************************************/
template<class T>
int Vector<T>::count(const T &value) const
{
    int count = 0;
    for (int i = 0; i < size(); ++i) {
        if(arrayPtr[i] == value){
            ++count;
        }
    }
    return count;
}

/*******************************************************************************
 * Inserts value at the end of the vector.
 * @param value to insert
 ******************************************************************************/
template<class T>
void Vector<T>::append(const T &value)
{
    push_back(value);
}

/*******************************************************************************
 * Inserts value at the beginning of the vector.
 * @param value to insert
 ******************************************************************************/
template<class T>
void Vector<T>::prepend(const T &value)
{
    push_front(value);
}

/*******************************************************************************
 * Replaces value at given index of the vector.
 * @param index in which to replace
 * @param value to insert
 ******************************************************************************/
template<class T>
void Vector<T>::replace(int index, const T &value)
{
    if(index < 0 || index >= size()){
        subError();
    }
    const T copy(value);
    arrayPtr[index]= copy;
}

/*******************************************************************************
 * removes index position and return its value
 * @param index to remove
 ******************************************************************************/
template<class T>
T Vector<T>::takeAt(int index)
{
    if(index < 0 || index >= size()){
        subError();
    }
    T copy(arrayPtr[index]);

    if(size() > 1){
        for(int i = index; i < size()-1; i++){
            arrayPtr[i] = arrayPtr[i+1];
        }
    }
    --arraySize;
    return copy;
}

/**
 * Inserts value at index position iindex in the vector.
 * If index is 0, the value is prepended to the vector.
 *  If index is size(), the value is appended to the vector.
 * @param index into which value is inserted
 * @param value to insert
 */
template<class T>
void Vector<T>::insert(int index, const T &value)
{
    if(index < 0 || index > size()){
        subError();
    }

    if(arraySize+1 > allocSize){// if adding a new element exceeds max size
        //calculate new allocSize
        int newMax = 1;
        while(newMax < size()+1){
            newMax*=2;
        }

        //allocate the appropriate memory
        T *newArray;
        try{
            newArray = new T[newMax];
        }catch(bad_alloc){
            memError();
        }

        //copy values to newArray
        for( int i=0; i<index;i++){
            newArray[i] = arrayPtr[i];
        }

        //add new item
        newArray[index] = value;

        for(int i = index; i <= size(); i++){
            newArray[i+1] = arrayPtr[i];
        }


        //delete old array
        delete arrayPtr;
        //set old array to point to new array
        arrayPtr = newArray;
        //set new allocSize
        allocSize = newMax;

    }else{//no new allocation needed for new value
        //shift all indexes above insertion point to the right in reverse order
        for(int i = size(); i > index; --i){
            arrayPtr[i] = arrayPtr[i-1];
        }
        //assign next key to new value
        arrayPtr[index]=value;
    }
    //increment arraySize to account
    arraySize++;

}

/*******************************************************************************
 * Sets the size of the vector to size. If size is greater than the current
 * size, elements are added to the end; the new elements are initialized with
 * a default-constructed value. If size is less than the current size, elements
 * are removed from the end.
 * @param size which to adjust vector
 ******************************************************************************/
template<class T>
void Vector<T>::resize(unsigned int newSize)
{
    if(newSize > allocSize){
        unsigned int newMax = 1;
        while(newMax < newSize){
            newMax *= 2;
        }

        T* newArray;
        try{
            newArray = new T[newMax];
        }catch(bad_alloc){
            memError();
        }

        for(int i= 0; i < size(); ++i){
           newArray[i] = arrayPtr[i];
        }

        delete arrayPtr;
        arrayPtr = newArray;

        allocSize = newMax;
        arraySize = newSize;
    }else {

        arraySize = newSize;
    }
}
/*******************************************************************************
 * Returns true if vector size  == 0;
 * @return true if vector is empty, false if not
 ******************************************************************************/
template<class T>
bool Vector<T>::isEmpty()
{
    return arraySize == 0;
}

/*******************************************************************************
 * Removes all the elements from the vector and releases the memory used by the
 *  vector.
 ******************************************************************************/
template<class T>
void Vector<T>::clear()
{
    if(arrayPtr){
        delete arrayPtr;
    }
    arrayPtr = 0;
    arraySize = 0;
    allocSize = 0;
}



#endif // SIMPLEVECTOR_H

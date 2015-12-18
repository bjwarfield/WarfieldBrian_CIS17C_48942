#ifndef HASH_H
#define HASH_H
#include <QtCore>
#include <iostream>
#include <string>
#include "GeneralHashFunctions.h"
//#include "Container/GeneralHashFunctions.h"



enum hashType{DEFAULT, RS, JS, PJW, ELF, BKDR, SBDM, DJB, DEK, BPH, FNV, APH};

template<class T>
class Hash
{
public:
    class iterator;
    struct node{
        QString key{};
        T value{};
        node *next;
    };

private:
    int tableWidth;
    hashType currentHashType;
    node* hashTable;
    int defaultHash(std::string key);
    int getHash(QString key);

public:
    Hash(int width, hashType type = DEFAULT);
    ~Hash();
    int Add(const QString &key, const T &value);
    int indexDepth(int index);
    T &operator [](QString key);
    void printTable();
    int width()const;
    int size()const;
    QString getHashType();

    iterator begin()    {
        int i = 0;
        while(hashTable[i].key.isEmpty() && i < tableWidth){
            i++;
        }
        return iterator(&hashTable[i], i, hashTable, tableWidth);


    }
    iterator end()
    {
        return iterator(&hashTable[tableWidth], tableWidth, hashTable, tableWidth);
    }

    friend class iterator;

    class iterator{
        friend class Hash;
    public:
        iterator(){current = NULL;}

        iterator(node *n, int i, node* t, int w){current = n; index = i;
                                                 table = t; width = w;}

        iterator(const iterator &it):current(it.current),index(it.index),
        table(it.table), width(it.width){}

        T &operator *()const{return current->value;}

        T *operator ->()const{return &current->value;}

        QString key()const{return current->key;}

        bool operator ==(const iterator &it)const{return current == it.current;}

        bool operator !=(const iterator &it)const{return current != it.current;}

        iterator &operator ++(){
            if(current->next){
                current = current->next;
            }else{
                do{//skip empty buckets
                    index++;
                }while(index < width && table[index].key.isEmpty());
                current = &table[index];
            }
            return *this;
        }


    private:
        node *current;
        int index;
        node *table;
        int width;

    };

};


template<class T>
Hash<T>::Hash(int size, hashType type):
    tableWidth(size), currentHashType(type)
{
    hashTable = new node[tableWidth];

    for (int i = 0; i < tableWidth; ++i) {
        hashTable[i].key = "";
        hashTable[i].next = NULL;

    }
}

template<class T>
Hash<T>::~Hash()
{

    for (int i = 0; i < tableWidth; ++i) {
        node *current;
        current = &hashTable[i];

        while(current->next != NULL){
            node * temp;
            temp = current->next;
            current->next = temp->next;
            delete temp;
        }
//        delete current;
    }
    delete[] hashTable;

}

template<class T>
int Hash<T>::Add(const QString &key, const T &value)
{
    int index = getHash(key);

    if(hashTable[index].key.size() == 0){
        hashTable[index].key = key;
        hashTable[index].value = value;
        hashTable[index].next = NULL;

    }else{
        node* worker;
        node * newNode = new node;

        worker = &hashTable[index];

        newNode->key = key;
        newNode->value = value;
        newNode->next = NULL;

        while(worker->next != NULL){
            worker = worker->next;
        }
        worker->next = newNode;
    }
    return indexDepth(index);
}

template<class T>
int Hash<T>::indexDepth(int index)
{
    int count = 0;
    if(hashTable[index].key.isEmpty()){
        return count;
    }else{
        count++;
        node* worker;
        worker = &hashTable[index];
        while(worker->next != NULL){
            count++;
            worker = worker->next;
        }

    }
    return count;
}

template<class T>
T &Hash<T>::operator [](QString key)
{
    int index = getHash(key);
    if(hashTable[index].key.isEmpty()){
        hashTable[index].key = key;
        return hashTable[index].value;
    }else{
        node *nodePtr;
        nodePtr = &hashTable[index];
        while(nodePtr->key.compare(key) != 0 && nodePtr->next != NULL){
            nodePtr = nodePtr-> next;
        }
        if(nodePtr->key.compare(key)== 0){
            return nodePtr->value;
        }
        node *newNode = new node;
        newNode->key = key;
        newNode->next = NULL;

        nodePtr->next = newNode;
        return newNode->value;
    }
}

template<class T>
void Hash<T>::printTable()
{
    int number;
    for (int i = 0; i < tableWidth; ++i) {

        number = indexDepth(i);

        node * nodePtr;
        nodePtr = &hashTable[i];

        while ( nodePtr != NULL){
            std::cout << "***********************************\n";
            std::cout << "index = " << i <<std::endl;
            std::cout << nodePtr->key.toLocal8Bit().constData() <<std::endl;
            std::cout << nodePtr->value << std::endl;
            std::cout << "Number of items = " << number <<std::endl;

            nodePtr = nodePtr->next;
        }

    }
}

template<class T>
int Hash<T>::width() const
{
    return tableWidth;
}

template<class T>
int Hash<T>::size()const
{
    int count = 0;
    for(int i = 0; i < tableWidth; i++){
        count += indexDepth(i);
    }
    return count;
}

template<class T>
int Hash<T>::defaultHash(std::string key)
{
    int h = 0;
    for(char c: key){
        h += static_cast<int>(c);
    }
    return h;
}

template<class T>
int Hash<T>::getHash(QString key)
{
    std::string keyString = key.toLocal8Bit().constData();
    int hashedIndex;

    switch(currentHashType){
        case RS:
            hashedIndex = RSHash(keyString);
            break;
        case JS:
            hashedIndex = JSHash(keyString);
            break;
        case PJW:
            hashedIndex = PJWHash(keyString);
            break;
        case ELF:
            hashedIndex = ELFHash(keyString);
            break;
        case BKDR:
            hashedIndex = BKDRHash(keyString);
            break;
        case SBDM:
            hashedIndex = SDBMHash(keyString);
            break;
        case DJB:
            hashedIndex = DJBHash(keyString);
            break;
        case DEK:
            hashedIndex = DEKHash(keyString);
            break;
        case BPH:
            hashedIndex = BPHash(keyString);
            break;
        case FNV:
            hashedIndex = FNVHash(keyString);
            break;
        case APH:
            hashedIndex = APHash(keyString);
            break;
        default:
            hashedIndex = defaultHash(keyString);
            break;
        }
    return qAbs(hashedIndex) % tableWidth;
}

template<class T>
QString Hash<T>::getHashType()
{
    switch(currentHashType){
    case RS:
        return "RSHash";
        break;
    case JS:
        return "JSHash";
        break;
    case PJW:
        return "PJWHash";
        break;
    case ELF:
        return "ELFHash";
        break;
    case BKDR:
        return "BKDRHash";
        break;
    case SBDM:
        return "SDBMHash";
        break;
    case DJB:
        return "DJBHash";
        break;
    case DEK:
        return "DEKHash";
        break;
    case BPH:
        return "BPHash";
        break;
    case FNV:
        return "FNVHash";
        break;
    case APH:
        return "APHash";
        break;
    default:
        return "defaultHash";
        break;
    }
}




#endif // HASH_H

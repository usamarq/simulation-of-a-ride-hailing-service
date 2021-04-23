/*Hash.h*/

#ifndef HASH_H
#define HASH_H

#include<iostream>
using namespace std;

template<class DT>
class Hash {
private:
    DT *hashTable;
    int size;
public:
    Hash(int s);
    bool store(DT key);
    DT operator[](int i) { return hashTable[i]; }
    int hash(DT key);
    void print();
};

template<class DT>
Hash<DT>::Hash(int s) : size(s) {
    hashTable = new DT[size];
    for (int i = 0; i < size; i++) {
        hashTable[i] = DT();
    }
}

template<class DT>
bool Hash<DT>::store(DT key) {
    bool added = false;
    int index = key % size;
    int init = index;
    while (!added) {
        if (hashTable[index] == DT()) {
            hashTable[index] = key;
            added = true;
        } else {
            if (hashTable[index] == key) {
                return false;
            }
            index = (index + 1) % size;
            if (index == init) {
                return false;
            }
        }

    }
    return added;
}

template<class DT>
int Hash<DT>::hash(DT key) {
    int index = key % size;
    int init = index;
    while (true) {
        if (hashTable[index] == key)
            return index;
        else {
            index = (index + 1) % size;
            if (index == init)
                return -1;
        }
    }
}

template<class DT>
void Hash<DT>::print() {
    for (int i = 0; i < size; i++)
        cout << i << '\t' << hashTable[i] << endl;
    cout << endl;
}

#endif // !HASH_H

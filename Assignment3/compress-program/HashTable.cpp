#include "HashTable.h"
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/* constructor */
HashTable::HashTable(int size) : array(nextPrime(size)) {
    makeEmpty();
    currentSize = 0;
}

/* private member functions */
// check if cell is active
bool HashTable::isActive(int currentPos) const {
    return array[currentPos].info == ACTIVE;
}

// perform linear probing, return the index where the search for x terminates
int HashTable::findPos(const string &x) const {
    int i = 0;
    
    int p = hash(x, array.size());
    
    while (array[p].info != EMPTY && array[p].element != x) {
        p += ++i;
        
        if (p >= array.size())
            p -= array.size();
    }
    
    return p;
}

// hash function which uses Horner's method
int HashTable::hash(const string &key, int tableSize) const {
	int sum = 0;

	for (int i = 0; i < key.length(); i++) {
		int add = key[i];
		if (add < 0)
			add = add * -1;

		sum = sum + add;
	}

	return (sum % tableSize);
}

// expand the array
void HashTable::rehash() {
    vector<HashEntry> oldArray = array;
    
    array.resize(nextPrime(2 * oldArray.size()));
}

/* methods to find the optimal size for the hashtable */
int HashTable::nextPrime(int n) {
    if (n % 2 == 0)
        n++;
    
    for (; !isPrime(n); n += 2)
        ;
    
    return n;
}

bool HashTable::isPrime(int n) {
    if (n == 2 || n == 3)
        return true;
    
    if (n == 1 || n % 2 == 0)
        return false;
    
    for (int i = 3; i * i <= n; i += 2)
        if (n % i == 0)
            return false;
    
    return true;
}

/* public member functions */
// find corresponding code given string
int HashTable::find(const string & x) const {
    int currentPos = findPos(x);
    
    if (isActive(currentPos))
        return array[currentPos].code;
    else
        return -1;
}

// make hashtable empty, by setting the state of all entries to EMPTY
void HashTable::makeEmpty() {
    for (int i = 0; i < array.size(); i++)
        if (array[i].info != EMPTY)
            array[i].info = EMPTY;
}

// insert given element to hashtable
void HashTable::insert(string x) {
    // maximum 4096 elements allowed, do not insert anything after that
    if (currentSize == 4096)
        return;
    
    int currentPos = findPos(x);
    
    if (isActive(currentPos))
        return;
    
    array[currentPos] = HashEntry(currentSize++, x, ACTIVE);
    
    if (currentSize >= array.size() / 2)
        rehash();
}

// remove given element from the hashtable, if exists
void HashTable::remove(const string &x) {
    int currentPos = findPos(x);
    
    if (isActive(currentPos)) {
        array[currentPos].info = DELETED;
        currentSize--;
    }
}

/* operator (=) overloading */
const HashTable & HashTable::operator=(const HashTable &rhs) {
    array = rhs.array;
    currentSize = rhs.currentSize;
    
    return *this;
}

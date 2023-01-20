#ifndef HashTable_h
#define HashTable_h

#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class HashTable {
public:
    explicit HashTable(int size);
    HashTable(const HashTable &rhs) : array(rhs.array), currentSize(rhs.currentSize) {}
    
    int find(const string &x) const;
    
    void makeEmpty();
    void insert(string x);
    void remove(const string &x);
    
    const HashTable &operator=(const HashTable &rhs);
    
    enum EntryType { ACTIVE, EMPTY, DELETED };
    
private:
    struct HashEntry {
        int code;
        string element;
        EntryType info;
        
        HashEntry(int c = -1, const string &e = "", EntryType i = EMPTY) : code(c), element(e), info(i) {}
    };
    
    vector<HashEntry> array;
    int currentSize;
    
    bool isActive(int currentPos) const;
    int findPos(const string &x) const;
    
    int hash(const string &key, int tableSize) const;
    void rehash();
    
    int nextPrime(int n);
    bool isPrime(int n);
    
};

#endif /* HashTable_h */

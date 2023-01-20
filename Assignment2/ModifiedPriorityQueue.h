#ifndef ModifiedPriorityQueue_h
#define ModifiedPriorityQueue_h

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct BuildingPoint { // struct where we keep each given point
    int label;
    int x;
    int value;
    bool isLeft;
    
    BuildingPoint (int lb=0, int xp=0, int val=0, bool il=false) : label(lb), x(xp), value(val), isLeft(il) {}
};

struct MpqObj { // struct kept inside heap containing label and value
    int value;
    int label;
    
    MpqObj (int v=0, int l=0) : value(0), label(0) {}
};

class ModifiedPriorityQueue { // heap class
private:
    int currentSize;
    vector<MpqObj> heap;
    vector<int> location;
    
    void buildHeap();
    void percolateDown(int hole);
    
public:
    ModifiedPriorityQueue(int capacity);
    ~ModifiedPriorityQueue();
    
    int getMax() const;
    bool isEmpty() const;
    
    void insert(int value, int label);
    int remove(int label);
};

#endif

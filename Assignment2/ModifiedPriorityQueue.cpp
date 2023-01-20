#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "ModifiedPriorityQueue.h"

using namespace std;

ModifiedPriorityQueue::ModifiedPriorityQueue(int capacity) { // initialize heap and location vectors
    int size = capacity / 2 + 1;
    heap = vector<MpqObj>(size);
    location = vector<int>(size);
    
    currentSize = 0;
}
 
ModifiedPriorityQueue::~ModifiedPriorityQueue() {
    currentSize = 0; // set currentSize to 0, meaning heap is now empty
}
 
void ModifiedPriorityQueue::buildHeap() {
    for (int i = currentSize / 2; i > 0; i--) // maintain heap order by percolating down
        percolateDown(i);
}
 
void ModifiedPriorityQueue::percolateDown(int hole) {
    int child;
    MpqObj tmp = heap[hole]; // item to percolate down
 
    for (; hole * 2 <= currentSize; hole = child) {
        child = hole * 2;
        if (child != currentSize && heap[child + 1].value < heap[child].value) // child is minimum of the children
            child++;
        if (heap[child].value < tmp.value) {
            heap[hole] = heap[child]; // swap hole and minimum child
            location[hole] = heap[child].label; // update location
        }
        else
            break;
    }
    
    heap[hole] = tmp; // place item to its final position
    location[hole] = tmp.label; // update location
}
 
int ModifiedPriorityQueue::getMax() const {
    if (isEmpty())
        return 0;
    
    int maxNum = heap[1].value;
    for (int i = 1; i <= currentSize; i++)
        maxNum = max(maxNum, heap[i].value); // find maximum element by comparing each element
    
    return maxNum;
}
 
bool ModifiedPriorityQueue::isEmpty() const {
    return currentSize == 0; // check currentSize, if it is zero: heap is empty
}
 
void ModifiedPriorityQueue::insert(int value, int label) {
    int hole = ++currentSize; // moving hole up
    
    for (; hole > 1 && value < heap[hole / 2].value; hole /= 2) {
        heap[hole] = heap[hole / 2]; // move hole
        location[hole] = heap[hole / 2].label; // update location
    }
    
    // update value & label
    heap[hole].value = value;
    heap[hole].label = label;
    location[hole] = label; // update location
}

int ModifiedPriorityQueue::remove(int label) {
    for (int i = 1; i <= location.size(); i++) {
        if (location[i] == label) { // if label found in location
            int remove = heap[i].value;
            swap(location[i], location[currentSize]); // swap location at index i with location at last index
            swap(heap[i], heap[currentSize]); // swap heap at index label with heap at index
            location[currentSize] = 0;
            heap[currentSize] = 0;
            currentSize--; // reduce size by one
            percolateDown(i); // maintaing heap order
            return remove;
        }
    }
    
    return 0;
}

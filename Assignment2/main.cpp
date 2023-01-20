#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "ModifiedPriorityQueue.h"

using namespace std;

vector<BuildingPoint> readFile(string fname, ifstream &in) { // read input file to a vector
    in.open(fname.c_str());
    
    int capacity = 0;
    string line;
    getline(in, line);
    istringstream ss(line);
    ss >> capacity;
    
    vector<BuildingPoint> buildings(capacity*2); // vector that we keep the points
    
    int label = 1;
    int index = 0;
    while (getline(in, line)) {
        istringstream ss2(line);
        int xLeft = 0, value = 0, xRight = 0;
        ss2 >> xLeft >> value >> xRight;
        
        BuildingPoint b1(label, xLeft, value, true); // read left endpoint
        BuildingPoint b2(label, xRight, value, false); // read right endpoint
        buildings[index] = b1; // insert left endpoint
        buildings[index+1] = b2; // insert right endpoint
        index += 2;
        label++;
    }
    
    in.close();
    
    return buildings;
}

bool compare(const BuildingPoint &lhs, const BuildingPoint &rhs) {
    if (lhs.x != rhs.x) // if x values are different
        return lhs.x < rhs.x;
    else {
        if (lhs.isLeft && rhs.isLeft) // if both points are left endpoints
            return lhs.value > rhs.value;
        
        else if (!lhs.isLeft && !rhs.isLeft) // if both points are right endpoints
            return lhs.value < rhs.value;
        
        else // if one point is left, other point is right endpoint
            return lhs.isLeft > rhs.isLeft;
    }
}

void getSkyline(vector<BuildingPoint> b) {
    int n = b.size();
    ModifiedPriorityQueue mpq(n);
    
    if (b[0].x != 0)
        cout << 0 << " " << 0 << endl;
    for (int i = 0; i < n; i++) {
        int currentMax = mpq.getMax();
        if (b[i].isLeft) { // if point is a left endpoint
            mpq.insert(b[i].value, b[i].label);
            int max = mpq.getMax();
            if (max != currentMax)
                cout << b[i].x << " " << b[i].value << endl;
        }
        else { // if point is a right endpoint
            mpq.remove(b[i].label);
            int max = mpq.getMax();
            if (max != currentMax)
                cout << b[i].x << " " << max << endl;
        }
    }
}
  
int main() {
    ifstream in;
    
    vector<BuildingPoint> buildings = readFile("input.txt", in);
    
    sort(buildings.begin(), buildings.end(), compare); // sort the vector that contains points
    getSkyline(buildings); // get skyline from given points
    
    return 0;
}

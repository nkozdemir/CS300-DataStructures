#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "PointQuadTree.h"

using namespace std;

void readCities(const string &fname, ifstream &in, PointQuadTree &qt) {
    in.open(fname.c_str());
    if(in.fail()) {
        cout << "Cannot open file " << fname << endl;
        return;
    }
    
    int x_limit = 0, y_limit = 0;
    string line;
    getline(in,line);
    istringstream ss(line);
    ss >> x_limit >> y_limit;
    while (getline(in, line)) {
        istringstream ss2(line);
        string cityName;
        int x_c = 0, y_c = 0;
        ss2 >> cityName >> x_c >> y_c;
        if ((x_c >= 0 && x_c <= x_limit) && (y_c >= 0 && y_c <= y_limit)) {
            qt.insert(cityName, x_c, y_c);
        }
    }
    
    in.close();
}

void readQueries(const string &fname, ifstream &in, PointQuadTree &qt) {
    in.open(fname.c_str());
    if(in.fail()) {
        cout << "Cannot open file " << fname << endl;
        return;
    }
    
    string line;
    int x_c = 0, y_c = 0, radius = 0;
    while (getline(in, line)) {
        line.erase(remove(line.begin(), line.end(), ','), line.end());
        istringstream ss(line);
        ss >> x_c >> y_c >> radius;
        qt.search(x_c, y_c, radius);
    }
    
    in.close();
}

int main() {
    PointQuadTree qt;
    
    ifstream in;
    readCities("cities.txt", in, qt);
    
    qt.prettyPrint();
    cout << endl;
    
    ifstream in2;
    readQueries("queries.txt", in2, qt);
    
    return 0;
}

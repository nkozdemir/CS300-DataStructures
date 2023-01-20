#include "PointQuadTree.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

PointQuadTree::PointQuadTree() { // constructor
    root = NULL;
}

PointQuadTree::~PointQuadTree() { // destructor
    makeEmpty();
}

void PointQuadTree::insert(const string &city_name, const int &x, const int &y) { // public insert function
    insert(city_name, x, y, root);
}

void PointQuadTree::insert(const string &city_name, const int &x, const int &y, QuadNode* &qn) const { // private insert function
    if (qn == NULL) {
        qn = new QuadNode(city_name, x, y);
    }
    else if (x < qn->xCoordinate) {
        if (y < qn->yCoordinate) {
            insert(city_name, x, y, qn->SW);
        }
        else {
            insert(city_name, x, y, qn->NW);
        }
    }
    else if (y < qn->yCoordinate) {
        insert(city_name, x, y, qn->SE);
    }
    else {
        insert(city_name, x, y, qn->NE);
    }
}

void PointQuadTree::prettyPrint() { // public print function
    prettyPrint(root);
}

void PointQuadTree::prettyPrint(QuadNode* &qn) const { // private print function
    if (qn != NULL) {
        cout << qn->cityName << endl;
        prettyPrint(qn->SE);
        prettyPrint(qn->SW);
        prettyPrint(qn->NE);
        prettyPrint(qn->NW);
    }
}

void PointQuadTree::search(const int &x, const int &y, const int &radius) { // public search function
    vector<string> citiesRadius;
    vector<string> citiesVisited;
    
    search(x, y, radius, root, citiesRadius, citiesVisited);
    
    if (citiesRadius.size() == 0) {
        cout << "<None>" << endl;
    }
    else {
        int n = citiesRadius.size();
        for (int i = 0; i < n-1; i++) {
            cout << citiesRadius[i] << ", ";
        }
        cout << citiesRadius[n-1] << endl;
    }
    
    int n = citiesVisited.size();
    for (int i = 0; i < n-1; i++) {
        cout << citiesVisited[i] << ", ";
    }
    
    cout << citiesVisited[n-1] << endl;
    cout << endl;
}

void PointQuadTree::search(const int &x, const int &y, const int &radius, QuadNode* &qn, vector<string> &citiesRadius, vector<string> &citiesVisited) const { // private search function
    if (qn == NULL) {
        return;
    }
    citiesVisited.push_back(qn->cityName);
    if(((qn->xCoordinate - x)*(qn->xCoordinate - x) + (qn->yCoordinate - y)*(qn->yCoordinate - y)) <= (radius*radius)) { //13
        citiesRadius.push_back(qn->cityName);
        search(x, y, radius, qn->SE, citiesRadius, citiesVisited);
        search(x, y, radius, qn->SW, citiesRadius, citiesVisited);
        search(x, y, radius, qn->NE, citiesRadius, citiesVisited);
        search(x, y, radius, qn->NW, citiesRadius, citiesVisited);
    }
    else if (x - radius > qn->xCoordinate && y + radius < qn->yCoordinate) { //1
        search(x, y, radius, qn->SE, citiesRadius, citiesVisited);
    }
    else if (x - radius > qn->xCoordinate && y + radius > qn->yCoordinate && y - radius < qn->yCoordinate) { //4
        search(x, y, radius, qn->SE, citiesRadius, citiesVisited);
        search(x, y, radius, qn->NE, citiesRadius, citiesVisited);
    }
    else if (x - radius > qn->xCoordinate && y - radius > qn->yCoordinate) { //6
        search(x, y, radius, qn->NE, citiesRadius, citiesVisited);
    }
    else if (x + radius < qn->xCoordinate && y + radius < qn->yCoordinate) { //3
        search(x, y, radius, qn->SW, citiesRadius, citiesVisited);
    }
    else if (x + radius < qn->xCoordinate && y + radius > qn->yCoordinate && y - radius < qn->yCoordinate) { //5
        search(x, y, radius, qn->SW, citiesRadius, citiesVisited);
        search(x, y, radius, qn->NW, citiesRadius, citiesVisited);
    }
    else if (x + radius < qn->xCoordinate && y - radius > qn->yCoordinate) { //8
        search(x, y, radius, qn->NW, citiesRadius, citiesVisited);
    }
    else if (x - radius < qn->xCoordinate && x + radius > qn->xCoordinate && y + radius < qn->yCoordinate) { //2
        search(x, y, radius, qn->SE, citiesRadius, citiesVisited);
        search(x, y, radius, qn->SW, citiesRadius, citiesVisited);
    }
    else if (x - radius < qn->xCoordinate && x + radius > qn->xCoordinate && y - radius > qn->yCoordinate) { //7
        search(x, y, radius, qn->NE, citiesRadius, citiesVisited);
        search(x, y, radius, qn->NW, citiesRadius, citiesVisited);
    }
    else if (x - radius < qn->xCoordinate && x > qn->xCoordinate && y < qn->yCoordinate && y + radius > qn->yCoordinate) { //9
        search(x, y, radius, qn->SE, citiesRadius, citiesVisited);
        search(x, y, radius, qn->SW, citiesRadius, citiesVisited);
        search(x, y, radius, qn->NE, citiesRadius, citiesVisited);
    }
    else if (x < qn->xCoordinate && x + radius > qn->xCoordinate && y < qn->yCoordinate && y + radius > qn->yCoordinate) { //10
        search(x, y, radius, qn->SE, citiesRadius, citiesVisited);
        search(x, y, radius, qn->SW, citiesRadius, citiesVisited);
        search(x, y, radius, qn->NW, citiesRadius, citiesVisited);
    }
    else if (x > qn->xCoordinate && x - radius < qn->xCoordinate && y > qn->yCoordinate && y - radius < qn->yCoordinate) { //11
        search(x, y, radius, qn->SE, citiesRadius, citiesVisited);
        search(x, y, radius, qn->NE, citiesRadius, citiesVisited);
        search(x, y, radius, qn->NW, citiesRadius, citiesVisited);
    }
    else if (x < qn->xCoordinate && x + radius > qn->xCoordinate && y > qn->yCoordinate && y - radius < qn->yCoordinate) { //12
        search(x, y, radius, qn->SW, citiesRadius, citiesVisited);
        search(x, y, radius, qn->NE, citiesRadius, citiesVisited);
        search(x, y, radius, qn->NW, citiesRadius, citiesVisited);
    }
    else if (qn->xCoordinate > x - radius && qn->xCoordinate < x && qn->yCoordinate == y + radius) { //A
        search(x, y, radius, qn->SE, citiesRadius, citiesVisited);
        search(x, y, radius, qn->SW, citiesRadius, citiesVisited);
        search(x, y, radius, qn->NE, citiesRadius, citiesVisited);
    }
    else if (x < qn->xCoordinate && x + radius > qn->xCoordinate && qn->yCoordinate == y + radius) { //B
        search(x, y, radius, qn->SE, citiesRadius, citiesVisited);
        search(x, y, radius, qn->SW, citiesRadius, citiesVisited);
        search(x, y, radius, qn->NW, citiesRadius, citiesVisited);
    }
    else if (x + radius == qn->xCoordinate && y < qn->yCoordinate && y + radius > qn->yCoordinate) { //C
        search(x, y, radius, qn->SE, citiesRadius, citiesVisited);
        search(x, y, radius, qn->SW, citiesRadius, citiesVisited);
        search(x, y, radius, qn->NW, citiesRadius, citiesVisited);
    }
    else if (x + radius == qn->xCoordinate && y > qn->yCoordinate && y - radius < qn->yCoordinate) { //D
        search(x, y, radius, qn->SW, citiesRadius, citiesVisited);
        search(x, y, radius, qn->NE, citiesRadius, citiesVisited);
        search(x, y, radius, qn->NW, citiesRadius, citiesVisited);
    }
    else if (x < qn->xCoordinate && x + radius > qn->xCoordinate && qn->yCoordinate == y - radius) { //E
        search(x, y, radius, qn->NE, citiesRadius, citiesVisited);
        search(x, y, radius, qn->NW, citiesRadius, citiesVisited);
    }
    else if (x > qn->xCoordinate && x - radius < qn->xCoordinate && qn->yCoordinate == y - radius) { //F
        search(x, y, radius, qn->NE, citiesRadius, citiesVisited);
        search(x, y, radius, qn->NW, citiesRadius, citiesVisited);
    }
    else if (x - radius == qn->xCoordinate && y > qn->yCoordinate && y - radius < qn->yCoordinate) { //G
        search(x, y, radius, qn->SE, citiesRadius, citiesVisited);
        search(x, y, radius, qn->NE, citiesRadius, citiesVisited);
    }
    else if (x - radius == qn->xCoordinate && y < qn->yCoordinate && y + radius > qn->yCoordinate) { //I
        search(x, y, radius, qn->SE, citiesRadius, citiesVisited);
        search(x, y, radius, qn->NE, citiesRadius, citiesVisited);
    }
    else if (x + radius < qn->xCoordinate && y + radius == qn->yCoordinate) { //P
        search(x, y, radius, qn->SW, citiesRadius, citiesVisited);
        search(x, y, radius, qn->NW, citiesRadius, citiesVisited);
    }
    else if (x + radius < qn->xCoordinate && y - radius == qn->yCoordinate) { //R
        search(x, y, radius, qn->NW, citiesRadius, citiesVisited);
    }
    else if (x + radius == qn->xCoordinate && y - radius > qn->yCoordinate) { //J
        search(x, y, radius, qn->NE, citiesRadius, citiesVisited);
        search(x, y, radius, qn->NW, citiesRadius, citiesVisited);
    }
    else if (x - radius == qn->xCoordinate && y - radius > qn->yCoordinate) { //K
        search(x, y, radius, qn->NE, citiesRadius, citiesVisited);
    }
    else if (x - radius > qn->xCoordinate && y - radius == qn->yCoordinate) { //L
        search(x, y, radius, qn->NE, citiesRadius, citiesVisited);
    }
    else if (x - radius > qn->xCoordinate && y + radius == qn->yCoordinate) { //M
        search(x, y, radius, qn->SE, citiesRadius, citiesVisited);
        search(x, y, radius, qn->NE, citiesRadius, citiesVisited);
    }
    else if (x - radius == qn->xCoordinate && y + radius < qn->yCoordinate) { //N
        search(x, y, radius, qn->SE, citiesRadius, citiesVisited);
    }
    else if (x + radius == qn->xCoordinate && y + radius < qn->yCoordinate) { //O
        search(x, y, radius, qn->SE, citiesRadius, citiesVisited);
        search(x, y, radius, qn->SW, citiesRadius, citiesVisited);
    }
    else if (x - radius == qn->xCoordinate && y + radius == qn->yCoordinate) { //X
        search(x, y, radius, qn->SE, citiesRadius, citiesVisited);
        search(x, y, radius, qn->NE, citiesRadius, citiesVisited);
    }
    else if (x + radius == qn->xCoordinate && y + radius == qn->yCoordinate) { //Y
        search(x, y, radius, qn->SE, citiesRadius, citiesVisited);
        search(x, y, radius, qn->SW, citiesRadius, citiesVisited);
        search(x, y, radius, qn->NW, citiesRadius, citiesVisited);
    }
    else if (x + radius == qn->xCoordinate && y - radius == qn->yCoordinate) { //Z
        search(x, y, radius, qn->NE, citiesRadius, citiesVisited);
        search(x, y, radius, qn->NW, citiesRadius, citiesVisited);
    }
    else if (x - radius == qn->xCoordinate && y - radius == qn->yCoordinate) { //W
        search(x, y, radius, qn->NE, citiesRadius, citiesVisited);
    }
    else {}
}

void PointQuadTree::makeEmpty() { // public delete function
    makeEmpty(root);
}

void PointQuadTree::makeEmpty(QuadNode* &qn) const { // private delete function
    if (qn != NULL) {
        makeEmpty(qn->SE);
        makeEmpty(qn->SW);
        makeEmpty(qn->NE);
        makeEmpty(qn->NW);
        delete qn;
    }
    
    qn = NULL;
}

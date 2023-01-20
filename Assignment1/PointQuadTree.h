#ifndef PointQuadTree_h
#define PointQuadTree_h

#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct QuadNode {
    string cityName;
    int xCoordinate, yCoordinate;
    QuadNode* NW;
    QuadNode* NE;
    QuadNode* SW;
    QuadNode* SE;
    
    QuadNode(const string &city_name, const int &x, const int &y, QuadNode* _NW=NULL, QuadNode* _NE=NULL, QuadNode* _SW=NULL, QuadNode* _SE=NULL)
    : cityName(city_name), xCoordinate(x), yCoordinate(y), NW(_NW), NE(_NE), SW(_SW), SE(_SE) {}
};

class PointQuadTree {
public:
    PointQuadTree();
    ~PointQuadTree();
    void insert(const string &city_name, const int &x, const int &y);
    void prettyPrint();
    void search(const int &x, const int &y, const int &radius);
    void makeEmpty();
private:
    QuadNode* root;
    void insert(const string &city_name, const int &x, const int &y, QuadNode* &qn) const;
    void prettyPrint(QuadNode* &qn) const;
    void search(const int &x, const int &y, const int &radius, QuadNode* &qn, vector<string> &citiesRadius, vector<string> &citiesVisited) const;
    void makeEmpty(QuadNode* &qn) const;
};


#endif /* PointQuadTree_h */

// main file for DECOMPRESSION
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

// create array and insert 256 characters
vector<string> initArray() {
    vector<string> array(4096);
    
    for (int i = 0; i < 256; i++) {
        string s = "";
        s += char(i);
     
        array[i] = s;
    }
     
    return array;
}

int main() {
    ifstream comp_out("compout");
    ofstream decomp_out("decompout");
    
    vector<string> array = initArray();
    
    // read first code, get corresponding string from array
    int ifc;
    comp_out >> ifc;
    string fcs = array[ifc];
    string fcc = "";
    fcc += fcs[0];
    decomp_out << fcs;
    
    int cd;
    int count = 256;
    while (comp_out >> cd) {
        if (array[cd].length() == 0) { // if corresponding string exist in array
            fcs = array[ifc];
            fcs = fcs + fcc;
        }
        else { // if corresponding string does not exist in array
            fcs = array[cd];
        }
        decomp_out << fcs;
        fcc = "";
        fcc += fcs[0];
        
        if (count < 4096)
            array[count] = array[ifc] + fcc;
        
        count++;
        ifc = cd;
    }
    
    comp_out.close();
    decomp_out.close();
    
    return 0;
}

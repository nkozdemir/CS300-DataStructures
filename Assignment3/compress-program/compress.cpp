// main file for COMPRESSION
#include <iostream>
#include <string>
#include <fstream>
#include "HashTable.h"

using namespace std;

// create hash table and insert 256 characters
HashTable initHashTable() {
    HashTable ht(4096);
    
    for (int i = 0; i < 256; i++) {
        string s = "";
        s += char(i);
     
        ht.insert(s);
    }
     
    return ht;
}

int main() {
    ifstream comp_in("compin");
    ofstream comp_out("compout");
    
    HashTable ht = initHashTable();
    
    // read first char
    char ch;
    comp_in.get(ch);
    
    string p = "";
    p += ch;
    
    char c;
    while (comp_in.get(c)) {
        string c_str = "";
        c_str += c;
        
        string s = ""; // previous char + current char
        s = p + c;
        
        if (ht.find(s) != -1) { // if corresponding code does not exist in hashtable
            p = s; // add to table
        }
        else { // if in table
            int code = ht.find(p);
            comp_out << code; // output corresponding code
            comp_out << " ";
            ht.insert(s); // insert to table
            p = c_str;
        }
    }
        
    int code = ht.find(p);
    comp_out << code;
    comp_out << " ";

    comp_in.close();
    comp_out.close();
    
    return 0;
}

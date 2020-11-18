// **************************************************************************
//  File       [MaxPlanarSubset.h]
//  Author     [b07901021 Shih-Hsuan Pan]
//  Synopsis   [The header file for the ChordSet, Node class]
//  Modify     [2020/11/8 Shih-Hsuan Pan]
// **************************************************************************

#ifndef _MAXPLANARSUBSET_H
#define _MAXPLANARSUBSET_H

#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

class ChordSet{
    friend class Node;
    public:
        ChordSet();
        ChordSet(int);
        bool connection_assign(int, int);
        int find_connection(int);
        bool chord_existence(int, int);
        void test();
    private:
        vector<int> data;

};

void traverse(int, int, ChordSet*, fstream &, int**);
#endif
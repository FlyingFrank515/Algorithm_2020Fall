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

class Node{
    public:
        Node();
        Node(vector<int>*);
        void data_assign(int);
        void data_clone(vector<int>*);
        vector<int>* get_data_address();
        int get_num();
        void print_all_chords(ChordSet*);
    private:
        vector<int>* data; // start points of all chords in range[i,j]
};

#endif
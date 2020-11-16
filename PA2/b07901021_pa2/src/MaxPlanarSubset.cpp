// **************************************************************************
//  File       [MaxPlanarSubset.cpp]
//  Author     [b07901021 Shih-Hsuan Pan]
//  Synopsis   [The implementation for the ChoreSet class]
//  Modify     [2020/11/8 Shih-Hsuan Pan]
// **************************************************************************
#include "MaxPlanarSubset.h"
using namespace std;

ChordSet::ChordSet() {}
ChordSet::ChordSet(int N){
    for(int i = 0; i < N; i++){
        data.push_back(0);
    }
}
bool ChordSet::connection_assign(int key, int connection){
    if(key < data.size() && connection < data.size()){
        data[key] = connection;
        return true;
    }
    else{
        cout << "Wrong input format !!" << endl;
        return false;
    }
}
int ChordSet::find_connection(int key){
    if(key < data.size())
        return data[key];
    else{
        cout << "Wrong input range of ChordSet !!" << endl;
        return -1;
    }
}
bool ChordSet::chord_existence(int A, int B){
    if(A >= data.size() || B >= data.size()) return false;
    else if(data[A] == B && data[B] == A) return true;
    return false;
}
void ChordSet::test(){
    for(int i = 0; i < data.size(); i++){
        cout << i << "---" << data[i] << endl;
    }
}

void traverse(int i, int j, ChordSet* C, vector<int>* list, int** M){
    int k = C->find_connection(j);
    if(!M[i][j]) return;
    else if((k > j) || (k < i)){    
        traverse(i, j-1, C, list, M);
    }
    
    else if(k == i){    
        list->push_back(i);
        traverse(i+1, j-1, C, list, M);
    }
    
    else if(k < j && k > i){                
        int A = M[i][j-1];
        int B = M[i][k-1] + 1 + M[k+1][j-1];
        if(A >= B){
            traverse(i, j-1, C, list, M);
        }
        else{
            traverse(i, k-1, C, list, M);
            list->push_back(k);
            traverse(k+1, j-1, C, list, M);
        }
    }

}
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
int MPS(int i, int j, ChordSet* C, int** M){
    // cout << "fill in " << "M[" << i << "][" << j << "]" << endl;
    if(M[i][j] != -1) return M[i][j];
    if(i >= j){
        M[i][j] = 0;
        return 0;
    }
    int k = C->find_connection(j);
    
    if((k > j) || (k < i)){    
        M[i][j] = MPS(i, j-1, C, M);
    }
    
    else if(k == i){    
        M[i][j] = MPS(i+1, j-1, C, M) + 1;
    }
    
    else if(k < j && k > i){                
        int A = MPS(i, j-1, C, M);
        int B = MPS(i, k-1, C, M) + 1 + MPS(k+1, j-1, C, M);
        M[i][j] = (A >= B) ? A : B;
    }
    return M[i][j];
}
void traverse(int i, int j, ChordSet* C, fstream& fout, int** M){
    
    if(!M[i][j]) return;
    int k = C->find_connection(j);
    
    if((k > j) || (k < i)){    
        traverse(i, j-1, C, fout, M);
    }
    
    else if(k == i){    
        fout << i << " " << j << endl;
        traverse(i+1, j-1, C, fout, M);
    }
    
    else if(k < j && k > i){                
        int A = M[i][j-1];
        int B = M[i][k-1] + 1 + M[k+1][j-1];
        if(A >= B){
            traverse(i, j-1, C, fout, M);
        }
        else{
            traverse(i, k-1, C, fout, M);
            fout << k << " " << j << endl;
            traverse(k+1, j-1, C, fout, M);
        }
    }

}
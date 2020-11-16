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

Node::Node(){new_chord = -1;}
Node::Node(int n, int x, int y){
    num = n;
    new_chord = -1;
    i = x;
    j = y;
}

void Node::path_assign(Node* n){
    path.push_back(n);
}

int Node::get_num(){
    return num;
}

void Node::num_assign(int n){
    num = n;
}

void Node::chord_assign(int c){
    new_chord = c;
}

void Node::traverse(vector<int>* list){
    // cout << "i,j=" << i  <<" "<< j << endl;
    // if(new_chord != -1){
    //     cout << "newly added: " << new_chord << endl;
    //     list->push_back(new_chord);
    // }
    // for(int k = 0; k < path.size(); k++){
    //     path[k]->traverse(list); 
    // }
}


void traverse(int i, int j, ChordSet* C, vector<int>* list, short** M){
    switch(M[i][j]){
        case 1:
            traverse(i, j-1, C, list, M);
            break;
        
        case 2:
            list->push_back(i);
            traverse(i+1, j-1, C, list, M);
            break;
        
        case 3:
            traverse(i, j-1, C, list, M);
            break;
        
        case 4:
            traverse(i, C->find_connection(j)-1, C, list, M);
            list->push_back(C->find_connection(j));
            traverse(C->find_connection(j)+1, j-1, C, list, M);
            break;
        
        default:
            return;
    }

}
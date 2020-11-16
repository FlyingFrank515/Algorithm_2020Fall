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

Node::Node(){}

Node::Node(vector<int>* d){
    data = d;
}
void Node::data_assign(int in){
    data->push_back(in);
}
void Node::data_clone(vector<int>* source){
    for(int i = 0; i < source->size(); i++){
        data->push_back((*source)[i]);
    }
}
vector<int>* Node::get_data_address(){
    return data;
}
int Node::get_num(){
    return data->size();
}
void Node::print_all_chords(ChordSet* connect){
    cout << "N = " << data->size() << endl;
    for(int i = 0; i < data->size(); i++){
        cout << (*data)[i] << " " << connect->find_connection((*data)[i]) << endl;
    }
}
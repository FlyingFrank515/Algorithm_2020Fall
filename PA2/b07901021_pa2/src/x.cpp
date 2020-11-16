// **************************************************************************
//  File       [main.cpp]
//  Author     [b07901021 Shih-Hsuan Pan]
//  Synopsis   [The main program of 2020 fall Algorithm PA2]
//  Modify     [2020/11/8 Shih-Hsuan Pan]
// **************************************************************************

#include <cstring>
#include <fstream>
#include <vector>
#include <algorithm> // for sorting vector
#include "MaxPlanarSubset.h"
bool DEBUG = true;

using namespace std;

void help_message() {
    cout << "usage: ./mps <input file> <output file>" << endl;
}

int main(int argc, char* argv[])
{
    if(argc != 3) {
       help_message();
       return 0;
    }

    //////////// read the input file /////////////
    
    if(DEBUG) cout << "reading..." << endl;
    char buffer[200];
    fstream fin(argv[1]);
    fstream fout;
    fout.open(argv[2],ios::out);
    int N; // the number of vertices on a circle
    fin >> N;
    vector<int> data; // 2i and 2i+1 represent two endpoints of a chord
    int num;
    while (fin >> num)
        data.push_back(num); // data[0] will be the first data. 
                             // data[1] will be the connection of first data.
    
    // test data 
    if(DEBUG){
        cout << "N = " << N << endl;
        cout << "data.size() = " << data.size() << endl;
        for(int i = 0; i < data.size(); i++){
            cout << data[i];
            cout << endl;
        }
    }

    // process the data
    if(DEBUG) cout << "processing..." << endl;
    ChordSet C(N);
    for(int i = 0; i < (N/2); i++){
        int first = data[2*i];
        int second = data[2*i+1];
        if(C.connection_assign(first, second) && C.connection_assign(second, first))
            continue;
        else
            return 0;
    }
    
    // test data after processing
    if(DEBUG) cout << "testing..." << endl;
    if(DEBUG) C.test();

    //////////// Algorithm ////////////
    if(DEBUG) cout << "counting..." << endl;
    
    vector<vector<Node>> M;
    for(int i = 0; i < N; i++){
        vector<Node> row;
        for(int j = 0; j <= i; j++){
            row.push_back(Node(0, i, j));
        }
        M.push_back(row);
    }
    for(int l = 1; l < N; l++){
        for(int i = 0; i < N - l; i++){
            int j = i + l;
            
            int k = C.find_connection(j);
            // if(DEBUG) cout << "assign M[" << i  << "][" << j << "]"<< endl; 
            
            if((k > j) || (k < i)){    
                M[i].push_back(Node(M[i][j-1].get_num(), i, j));
                M[i][j].path_assign(&(M[i][j-1]));
            }
            
            else if(k == i){    
                M[i].push_back(Node(M[i+1][j-1].get_num(), i, j));
                M[i][j].path_assign(&(M[i+1][j-1]));
                M[i][j].chord_assign(k);
            }
            
            else if(k < j && k > i){
                int A = M[i][j-1].get_num();
                int B = M[i][k-1].get_num() + 1 + M[k+1][j-1].get_num();
                
                if(A >= B){
                    M[i].push_back(Node(A, i, j));
                    M[i][j].path_assign(&(M[i][j-1]));
                }
                else{
                    M[i].push_back(Node(B, i, j));
                    M[i][j].path_assign(&(M[i][k-1]));
                    M[i][j].path_assign(&(M[k+1][j-1]));
                    M[i][j].chord_assign(k);
                }
            }
            else{ cout << "FUCKED UP" << endl;}
        }
    }
    
    if(DEBUG) cout << "writing output..." << endl;    
    
    vector<int> chordlist;
    
    M[0][N-1].traverse(&chordlist);
    if(DEBUG){
        cout << "N = " << chordlist.size() << endl;
        for(int i = 0; i < chordlist.size(); i++){
            cout << chordlist[i] << " " <<  C.find_connection(chordlist[i]) << endl;
        }
    }
    if(DEBUG) cout << "starting sort..." << endl;
    sort(chordlist.begin(), chordlist.end());
    
    if(DEBUG){
        cout << "N = " << chordlist.size() << endl;
        for(int i = 0; i < chordlist.size(); i++){
            cout << chordlist[i] << " " <<  C.find_connection(chordlist[i]) << endl;
        }
    }
    
    // need to be modified
    //////////// write the output file ///////////
    
    fout << chordlist.size() << endl;
    for(int i = 0; i < chordlist.size(); i++){
        fout << chordlist[i] << " " <<  C.find_connection(chordlist[i]) << endl;
    }
    fin.close();
    fout.close();
    return 0;
}

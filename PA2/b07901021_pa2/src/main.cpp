// **************************************************************************
//  File       [main.cpp]
//  Author     [b07901021 Shih-Hsuan Pan]
//  Synopsis   [The main program of 2020 fall Algorithm PA2]
//  Modify     [2020/11/8 Shih-Hsuan Pan]
// **************************************************************************

#include <cstring>
#include <fstream>
#include <vector>
#include "MaxPlanarSubset.h"
bool DEBUG = false;

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
    vector<vector<Node>> M;
    vector<int>* blank = new vector<int>;
    for(int i = 0; i < N; i++){
        vector<Node> row;
        for(int j = 0; j <= i; j++){
            row.push_back(Node(blank));
        }
        M.push_back(row);
    }
    for(int l = 1; l < N; l++){
        for(int i = 0; i < N - l; i++){
            int j = i + l;
            int k = C.find_connection(j);
            if(DEBUG) cout << "assign M[" << i  << "][" << j << "]"<< endl; 
            if(!((k <= j) && (k >= i))){
                M[i].push_back(Node(M[i][j-1].get_data_address()));
                // M[i][j].data_clone(M[i][j-1].get_data_address());
            }
            else if(k == i){
                vector<int>* temp = new vector<int>;
                vector<int>* ori = M[i+1][j-1].get_data_address();
                for(int z = 0; z < ori->size(); z++){
                    temp->push_back((*ori)[z]);
                }
                M[i].push_back(temp);
                M[i][j].data_assign(k);
            }
            else{
                int A = M[i][j-1].get_num();
                int B = M[i][k-1].get_num() + 1 + M[k+1][j-1].get_num();
                if(A >= B){
                    M[i].push_back(Node(M[i][j-1].get_data_address()));
                    // M[i][j].data_clone(M[i][j-1].get_data_address());
                }
                else{
                    vector<int>* temp = new vector<int>;
                    vector<int>* ori = M[i][k-1].get_data_address();
                    for(int z = 0; z < ori->size(); z++){
                        temp->push_back((*ori)[z]);
                    }
                    temp->push_back(k);
                    ori = M[k+1][j-1].get_data_address();
                    for(int z = 0; z < ori->size(); z++){
                        temp->push_back((*ori)[z]);
                    }
                    M[i].push_back(Node(temp));
                }
            }
        }
    }
    if(DEBUG) M[0][N-1].print_all_chords(&C);

    
    // need to be modified
    //////////// write the output file ///////////
    
    fout << M[0][N-1].get_num() <<endl;
    vector<int>* chords = M[0][N-1].get_data_address();
    for (int i = 0; i < chords->size(); i++)
        fout << (*chords)[i] << " " << C.find_connection((*chords)[i]) << endl;
    fin.close();
    fout.close();
    return 0;
}

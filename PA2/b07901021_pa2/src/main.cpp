// **************************************************************************
//  File       [main.cpp]
//  Author     [b07901021 Shih-Hsuan Pan]
//  Synopsis   [The main program of 2020 fall Algorithm PA2]
//  Modify     [2020/11/8 Shih-Hsuan Pan]
// **************************************************************************

#include <cstring>
#include <fstream>
#include <vector>
#include "../lib/tm_usage.h"
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
    CommonNs::TmUsage tmusg;
    CommonNs::TmStat stat;

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
    tmusg.periodStart();
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

    int **M = new int* [N];
    for(int i = 0; i < N; i++){
        M[i] = new int[N];
    }
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            M[i][j] = -1;
        } 
    }
    
    M[0][N-1] = MPS(0, N-1, &C, M);
    
    // for(int l = 0; l < N; l++){
    //     for(int i = 0; i < N - l; i++){        
    //         int j = i + l;      
    //         if(i == j){
    //             M[i][j] = 0;
    //             continue;
    //         } 
    //         int k = C.find_connection(j);
            
    //         if((k > j) || (k < i)){    
    //             M[i][j] = M[i][j-1];
    //         }
            
    //         else if(k == i){    
    //             M[i][j] = M[i+1][j-1] + 1;
    //         }
            
    //         else if(k < j && k > i){                
    //             int A = M[i][j-1];
    //             int B = M[i][k-1] + 1 + M[k+1][j-1];
    //             if(A >= B){
    //                 M[i][j] = A;
    //             }
    //             else{
    //                 M[i][j] = B;
    //             }
    //         }
    //     }
    // }
    
    //////////// write the output file ///////////
    fout << M[0][N-1] << endl;
    traverse(0, N-1, &C, fout, M);
    
    //////////// report time and memory///////////
    tmusg.getPeriodUsage(stat);
    cout <<"The total CPU time: " << (stat.uTime + stat.sTime) / 1000.0 << "ms" << endl;
    cout <<"memory: " << stat.vmPeak << "KB" << endl; // print peak memory
    
    fin.close();
    fout.close();
    return 0;
}

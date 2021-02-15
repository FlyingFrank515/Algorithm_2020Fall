// **************************************************************************
//  File       [main.cpp]
//  Author     [b07901021 Shih-Hsuan Pan]
//  Synopsis   [The main program of 2020 fall Algorithm PA3]
//  Modify     [2020/12/16 Shih-Hsuan Pan]
// **************************************************************************

#include <cstring>
#include <fstream>
#include <vector>
#include <iostream>
#include "CycleBreaking.h"
#include "../lib/tm_usage.h"

bool DEBUG = false;

using namespace std;

void help_message() {
    cout << "usage: ./cb <input file> <output file>" << endl;
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
    char type; // 'u' means undirected edge
               // 'd' means directed edge
    fin >> type;
    int m, n; // n: total number of vertices 
              // m: total number of edges
    fin >> n >> m;
    
    vector<int> data;
    int num;
    while (fin >> num)
        data.push_back(num); // data[3i] will be the start point of an edge. 
                             // data[3i+1] will be the end point of an edge. 
                             // data[3i+2] will be the weight.
    
    // test data 
    if(DEBUG){
        cout << "type = " << type << endl;
        cout << "# of vertices = " << n << endl;
        cout << "# of edges = " << m << endl;
        for(int i = 0; i < data.size(); i++){
            cout << data[i];
            cout << endl;
        }
    }
    
    tmusg.periodStart();
    // process the data
    if(DEBUG) cout << "processing..." << endl;
    Graph G(type, n);
    for(int i = 0; i < m; i++){
        int u = data[3*i];
        int v = data[3*i+1];
        int w = data[3*i+2];
        G.E_construct(u, v, w);
    }
    
    // test data after processing
    if(DEBUG) cout << "testing..." << endl;
    if(DEBUG) G.test();

    //////////// Algorithm ////////////
    G.cyclebreak(fout);

    //////////// report time and memory///////////
    tmusg.getPeriodUsage(stat);
    cout <<"The total CPU time: " << (stat.uTime + stat.sTime) / 1000.0 << "ms" << endl;
    cout <<"memory: " << stat.vmPeak << "KB" << endl; // print peak memory
    
    fin.close();
    fout.close();
    return 0;
}

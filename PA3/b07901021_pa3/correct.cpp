// this is the checker for PA3, NTUEE, algorithm, 2020 fall
// produced by b07901021 SHIH-HSUAN PAN in 2020/12/20
// compile:    g++ correct.cpp -o correct
// run:        ./correct <original_input_file> <output_file_you_produced>
// 
// (1) the program will first read the original input file and construct graph 
//     (only consider the edge without considering the weight)
// (2) then the output file you produced will be readed
// (3) according to your output file, some edges in the graph will be removed
//     also, the program will check whether the edge you removed is in the original input file   
//     however, the order of undirected edges doesnt follow the order in the original input file 
// (4) then the program will run DFS-smiliary algorithm to check the existence of cycles
// (5) treating all directed edges as undirected, then start traverse all vertices to see 
//     whether all vertices are weakly connected
// 
// summary:
// the program will check
// (1) whether you delete some edges not in the original input file
// (2) whether all vertices are weakly connected
// (3) whether there is any cycle in your graph aftering removing edges you specified
// 
// if there is any problem about this checker, please send email to me to discuss about it
// email: b07901021@ntu.edu.tw

#include <cstring>
#include <fstream>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

class Graph
{
    public:
        Graph();
        Graph(char , int);
        void E_construct(int, int);
        void E_delete(int, int);
        void DFS_cycle_detecting_check();
        void DFS_visit_check(int, vector<char>&, vector<int>&);
        void weakly_connected_check();
        void traverse(int, vector<char>&, vector<vector<int> >&);
    private:
        char type;
        int n;
        vector<vector<int> > adj;
};

Graph::Graph(char t, int num){
    type = t;
    n = num;
    for(int i = 0; i < n; i++){
        vector<int> blank;
        adj.push_back(blank);
    }
}
void Graph::E_construct(int u, int v){
    adj[u].push_back(v);
    if(type == 'u') adj[v].push_back(u);
}

void Graph::E_delete(int u, int v){
    if(type == 'd'){
        // cout << "deleting edge(" << u << ", " << v << ")" << endl;
        vector<int>::iterator it = find (adj[u].begin(), adj[u].end(), v);
        if (it != adj[u].end()) adj[u].erase(it);
        else cout << "wrong!! your output file deletes edge not in original input file" << endl;
    }
    else{
        vector<int>::iterator it1 = find (adj[u].begin(), adj[u].end(), v);
        vector<int>::iterator it2 = find (adj[v].begin(), adj[v].end(), u);
        if (it1 != adj[u].end() && it2 != adj[v].end()) {
            adj[u].erase(it1);
            adj[v].erase(it2);
            // cout << "deleting edge(" << u << ", " << v << ")" << endl;
        }
        else{
            cout << "wrong!! your output file deletes edge not in original input file" << endl;
        } 
    }
}

void Graph::DFS_cycle_detecting_check(){
    vector<char> color(n, 'w'); 
    vector<int> pi(n, -1); 
    for(int i = 0; i < n; i++){
        if(color[i] == 'w')
            DFS_visit_check(i, color, pi);
    }
}
void Graph::DFS_visit_check(int u, vector<char>& color, vector<int>& pi){
    color[u] = 'g';
    for(int i = 0; i < adj[u].size(); i++){
        int v = adj[u][i];
        if(color[v] == 'w'){
            pi[v] = u;
            DFS_visit_check(v, color, pi);
        }
        else if(color[v] == 'g' && type == 'd'){
            cout << "wrong!! there are cycles in your graph" << endl;
        }
        else if(color[v] == 'g' && type == 'u'){
            if(v != pi[u])
                cout << "wrong!! there are cycles in your graph" << endl;
        }
    }
    color[u] = 'b';
}
void Graph::weakly_connected_check(){
    vector<vector<int> > adj_matrix;
    vector<char> color(n, 'w');
    for(int i = 0; i < n; i++){
        vector<int> temp(n, 0);
        adj_matrix.push_back(temp);
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < adj[i].size(); j++){
            int u = i;
            int v = adj[i][j];
            adj_matrix[u][v] = 1;
            adj_matrix[v][u] = 1;
        }
    }
    traverse(0, color, adj_matrix);
    for(int i = 0; i < n; i++){
        if(color[i] == 'w'){
            cout << "wrong!! all vertices are not weakly connected" << endl;
            break;
        }
    }

}
void Graph::traverse(int u, vector<char>& color, vector<vector<int> >& m){
    color[u] = 'g';
    for(int i = 0; i < m[u].size(); i++){
        if(m[u][i] == 1){
            int v = i;
            if(color[v] == 'w'){
                traverse(v, color, m);
            }
        }
    }
    color[u] = 'b';
}

int main(int argc, char* argv[])
{
    if(argc != 3) {
       cout << "wrong arguments" << endl;
       return 0;
    }

    //////////// read the input file /////////////
    
    cout << "reading..." << endl;
    char buffer[200];
    fstream fin(argv[1]);
    fstream fin_d(argv[2]);
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
    
    cout << "processing original input file..." << endl;
    Graph G(type, n);
    for(int i = 0; i < m; i++){
        int u = data[3*i];
        int v = data[3*i+1];
        int w = data[3*i+2];
        G.E_construct(u, v);
    }

    cout << "processing output file..." << endl;
    vector<int> data_d;
    int num_d, total;
    fin_d >> total;
    cout << "sum of deleted edge weight = " << total << endl;
    while (fin_d >> num_d){
        data_d.push_back(num_d);
    }
    for(int i = 0; i < data_d.size(); i+=3){
        int u = data_d[i];
        int v = data_d[i+1];
        int w = data_d[i+2];
        G.E_delete(u, v);
    }

    cout << "checking cycle existance" << endl;
    G.DFS_cycle_detecting_check();

    cout << "checking connected" << endl;
    G.weakly_connected_check();

    cout << "checking finished" << endl;
}
    
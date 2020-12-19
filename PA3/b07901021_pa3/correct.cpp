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
    private:
        char type;
        int n;
        vector<vector<int>> adj;
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
        cout << "deleting edge(" << u << ", " << v << ")" << endl;
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
            cout << "deleting edge(" << u << ", " << v << ")" << endl;
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
    for(int i = 0; i < n; i++){
        if(color[i] != 'b'){
            cout << "weong!! there are some verices that are not be connected" << endl;
        }
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
    int num_d, garbage;
    fin_d >> garbage;
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

    cout << "checking finished" << endl;
}
    
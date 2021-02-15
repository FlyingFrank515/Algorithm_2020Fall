#include <iostream>
#include <vector>
#include <iomanip>
#include <climits>
#include <algorithm>
#include <fstream>
using namespace std;

class Vertex
{
    friend class Graph;
    friend class Edge;
    public:
        Vertex();
        Vertex(int, int);
    private:
        int key;
        int pi;
        int root;
        int rank;
};

class Edge
{
    friend class Graph;
    friend class Vertex;
    public:
        Edge();
        Edge(int, int, int);
    private:
        int start, end;
        int weight;
};

class Graph
{
    public:
        Graph();
        Graph(char, int);
        void E_construct(int, int, int);
        void test();
        void cyclebreak(fstream&);
        void sort_E();
        void MST_Kruskal();
        void dir_find_delete_edge(vector<Edge>&);
        void add_edge_back(vector<Edge>&);
        void output_u(fstream&);
        void output_d(fstream&);
    private:
        void Makeset(int);
        void Union(int, int);
        int Findset(int);
        void Link(int, int);
        void MergeSort(vector<Edge>&);
        void MergeSortSubVector(vector<Edge>&, int, int);
        void Merge(vector<Edge>&, int, int, int, int);

        bool DFS_cycle_detecting(Edge&);
        bool DFS_visit(int, int, vector<char>&);

        void DFS_cycle_detecting_check();
        void DFS_visit_check(int, vector<char>&);
        
        char type;
        int n;
        // weight[i][j] means the weight of edge(i,j)(-100~100)
        // if no edges between (i,j), weight[i][j] = 666
        vector<vector<int> > weight;
        vector<vector<int> > A;
        vector<Edge> E;
        vector<vector<int> > adj;
        vector<Vertex> V;
};


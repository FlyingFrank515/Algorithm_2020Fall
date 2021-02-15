#include "CycleBreaking.h"

Graph::Graph(){}
Graph::Graph(char t, int num){
    type = t;
    n = num;
    if(type != 'u' && type != 'd')
        cout << "Wrong input format, type must be 'u' or 'd'" << endl;
    for(int i = 0; i < n; i++){
        vector<int> temp(n, 666);
        vector<int> blank;
        Vertex t(0,0);
        weight.push_back(temp);
        A.push_back(temp);
        adj.push_back(blank);
        V.push_back(t);

    }
    // for(int i = 0; i < n; i++){
    //     weight[i][i] = 0;
    // }
    
}
void Graph::E_construct(int u, int v, int w){
    if(u >= n){
        cout << "Wrong input edge format" << endl;
        return;
    }
    if(v >= n){
        cout << "Wrong input edge format" << endl;
        return;
    }
    weight[u][v] = w;
    adj[u].push_back(v);
    Edge e(u,v,w);
    E.push_back(e);
    if(type == 'u'){
        weight[v][u] = w;
        adj[v].push_back(u);
    }
}
void Graph::test(){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cout << left << setw(4) << weight[i][j];
        }
        cout << endl;
    }
}

void Graph::cyclebreak(fstream& fout){
    if(type == 'u'){
        // undirected:
        // (1) find the minimum spanning tree
        // (2) compare the MST to origin edge and find the deleted edge
        MST_Kruskal();
        output_u(fout);
    }
    else if(type == 'd'){
        // directed:
        // (1) treat all edges as undirected edges and find the minimum spanning tree
        // (2) compare the MST to origin edge and find the deleted 
        // (3) trying add back edges with "positive weight" in decreasing order
        // (4) run DFS to check whether the edge added will cause cycle in the Graph
        // (5) if not, add it back
        // (6) compare the final result to origin edge and find the deleted edge
        
        MST_Kruskal();
        vector<Edge> d;
        dir_find_delete_edge(d);
        add_edge_back(d);
        output_d(fout);
    }
    else{
        cout << "type error" << endl;
    }
}

void Graph::MST_Kruskal(){
    for(int i = 0; i < n; i++){
        Makeset(i);
    }
    sort_E();    
    for(int i = 0; i < E.size(); i++){
        int u = E[i].start;
        int v = E[i].end;
        if(Findset(u) != Findset(v)){
            A[u][v] = E[i].weight;
            if(type == 'u') A[v][u] = E[i].weight;
            Union(u, v);
        }
    }
}

void Graph::sort_E(){
    MergeSort(E);
}
void Graph::dir_find_delete_edge(vector<Edge>& d){
    int total_w = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(weight[i][j] != A[i][j]){
                Edge temp(i, j ,weight[i][j]);
                d.push_back(temp);
                vector<int>::iterator it = find (adj[i].begin(), adj[i].end(), j);
                if (it != adj[i].end())
                    adj[i].erase(it);
                else cout << "strange" << endl;
            }
        }
    }
}

void Graph::add_edge_back(vector<Edge>& d){
    MergeSort(d);
    for(int i = 0; i < d.size(); i++){
        if(d[i].weight > 0)
            if(!DFS_cycle_detecting(d[i])){
                adj[d[i].start].push_back(d[i].end);
                A[d[i].start][d[i].end] = weight[d[i].start][d[i].end];
            }
    }
}

// return true if adding this edge will lead to new cycle
bool Graph::DFS_cycle_detecting(Edge& d){
    vector<char> color(n, 'w'); 
    return DFS_visit(d.start, d.end, color);
}

// return true if finding cycle
bool Graph::DFS_visit(int target, int u, vector<char>& color){
    color[u] = 'g';
    for(int i = 0; i < adj[u].size(); i++){
        int v = adj[u][i];
        if(v == target) return true;
        if(color[v] == 'w'){
            if(DFS_visit(target, v, color)) return true;
        }
    }
    color[u] = 'b';
    return false;
}


void Graph::output_u(fstream& fout){
    vector<int> u, v, w;
    int total_w = 0;
    for(int i = 0; i < n; i++){
        for(int j = i; j < n; j++){
            if(A[i][j] != weight[i][j]){
                u.push_back(i);
                v.push_back(j);
                w.push_back(weight[i][j]);
                total_w += weight[i][j];
            }
        }
    }
    fout << total_w << endl;
    for(int i = 0; i < u.size(); i++){
        fout << u[i] << " " << v[i] << " " << w[i] << endl;
    }
}

void Graph::output_d(fstream& fout){
    vector<int> u, v, w;
    int total_w = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(weight[i][j] != A[i][j]){
                u.push_back(i);
                v.push_back(j);
                w.push_back(weight[i][j]);
                total_w += weight[i][j];
            }
        }
    }
    fout << total_w << endl;
    for(int i = 0; i < u.size(); i++){
        fout << u[i] << " " << v[i] << " " << w[i] << endl;
    }
    
    // check for validity
    // create an new graph then check whether there are cycles
    
    ////---------------------------------------------------------------------
    // Graph G_check(type, n);
    // int total = 0;
    // for(int i = 0; i < n; i++){
    //     for(int j = 0; j < n; j++){
    //         if(A[i][j] != 666){
    //             total++;
    //             G_check.E_construct(i, j, A[i][j]);
    //         }
    //     }
    // }
    // cout << "there are " << total << " edges"  << endl;
    // DFS_cycle_detecting_check();
    ////----------------------------------------------------------------------
}

void Graph::DFS_cycle_detecting_check(){
    vector<char> color(n, 'w'); 
    for(int i = 0; i < n; i++){
        if(color[i] == 'w')
            DFS_visit_check(i, color);
    }
}
void Graph::DFS_visit_check(int u, vector<char>& color){
    color[u] = 'g';
    for(int i = 0; i < adj[u].size(); i++){
        int v = adj[u][i];
        if(color[v] == 'w'){
            DFS_visit_check(v, color);
        }
        else if(color[v] == 'g'){
            cout << "wrong!! there are cycles in your graph" << endl;
        }
    }
    color[u] = 'b';
}

void Graph::Makeset(int x){
    V[x].root = x;
    V[x].rank = 0;
}
void Graph::Union(int x, int y){
    Link(Findset(x), Findset(y));
}
int Graph::Findset(int x){
    if(x != V[x].root)
        V[x].root = Findset(V[x].root);
    return V[x].root;
}
void Graph::Link(int x, int y){
    if(V[x].rank > V[y].rank)   
        V[y].root = x;
    else{
        V[x].root = y;
        if(V[x].rank == V[y].rank)  
            V[y].rank += 1;
    }
}

Vertex::Vertex(){}
Vertex::Vertex(int k, int p){
    key = k;
    pi = -1;
    root = -1;
    rank = 0;
}

Edge::Edge(){}
Edge::Edge(int s, int e, int w){
    start = s;
    end = e;
    weight = w;
}

// decreasing order
void Graph::MergeSort(vector<Edge>& data){
    MergeSortSubVector(data, 0, data.size() - 1);
}
void Graph::MergeSortSubVector(vector<Edge>& data, int low, int high) {
    // Function : Merge sort subvector
    // TODO : Please complete MergeSortSubVector code here
    // Hint : recursively call itself
    //        Merge function is needed
    if(high > low){
        int mid = (high + low);
        if((mid % 2) == 0) mid = mid/2;
        else mid = (mid-1)/2;
        MergeSortSubVector(data, low, mid);
        MergeSortSubVector(data, mid+1, high);
        Merge(data, low, mid, mid+1, high);
    }
}
void Graph::Merge(vector<Edge>& data, int low, int middle1, int middle2, int high){
    // Function : Merge two sorted subvector
    // TODO : Please complete the function
    int len1 = middle1 - low + 1;
    int len2 = high - middle2 +1;
    vector<Edge> L, R;
    for(int i = 0; i < len1 ; i++){
        L.push_back(data[i+low]);
    }
    for(int i = 0; i < len2 ; i++){
        R.push_back(data[i+middle2]);
    }
    int i = 0; 
    int j = 0;
    for(int k = 0; k < high - low +1; k++){
        if(i == len1){
            data[low+k] = R[j];
            j++;
        }
        else if(L[i].weight > R[j].weight || j == len2){
            data[low+k] = L[i];
            i++;
        }
        else{
            data[low+k] = R[j];
            j++;
        }
    }
}
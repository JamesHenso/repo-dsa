#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
#include <queue>
#include <stack>


using namespace std;

// --- Define function prototypes ---
vector<vector<int>> general(vector<vector<int>> adjMatrix);
vector<vector<int>> convertMatrixToList(const string &filename);
vector<vector<int>> convertListToMatrix(const string &filename);
bool isDirected(const vector<vector<int>> &adjMatrix);
int countVertices(const vector<vector<int>> &adjMatrix);
int countEdges(const vector<vector<int>> &adjMatrix);
vector<int> getIsolatedVertices(const vector<vector<int>> &adjMatrix);
bool isCompleteGraph(const vector<vector<int>> &adjMatrix);
bool isBipartite(const vector<vector<int>> & adjMatrix);
bool isCompleteBipartite(const vector<vector<int>> &adjMatrix);
vector<vector<int>> convertToUndirectedGraph(const vector<vector<int>>& adjMatrix);
vector<vector<int>> dfsSpanningTree(const vector<vector<int>> &adjMatrix, int start);
vector<vector<int>> bfsSpanningTree(const vector<vector<int>> &adjMatrix, int start);
vector<vector<int>> getComplementGraph(const vector<vector<int>> &adjMatrix);
vector<int> Euler_Undirected(vector<vector<int>> adjMatrix, int start);
vector<int> Euler_Directed(vector<vector<int>> adjMatrix, int start);
bool hasEulerCycleUndirected(const vector<vector<int>>& adjMatrix);
bool hasEulerCycleDirected(const vector<vector<int>>& adjMatrix);
bool hasEulerCycle(const vector<vector<int>>& adjMatrix);
vector<int> findEulerCycle(const vector<vector<int>>& adjMatrix);
vector<int> dijkstra(int start, int end, const vector<vector<int>>& adjMatrix);
vector<int> bellmanFord(int start, int end, const vector<vector<int>>& adjMatrix);
// _________________________________________________________________

vector<vector<int>> general(vector<vector<int>> adjMatrix){
    int rows = adjMatrix.size();
    int cols = adjMatrix[0].size();
    vector<vector<int>> res(rows);
    for(int i = 0; i < rows; i++){
        vector<int> temp;
        for(int j = 0; j < cols; j++){

            if(adjMatrix[i][j]) temp.push_back(j);
        }
        res[i] = temp;
    }
    return res;
}

vector<vector<int>> convertMatrixToList(const string &filename) {
    ifstream file_in(filename);
    vector<vector<int>> adjList;
    if (!file_in.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return adjList;
    }

    string line;
    if (!getline(file_in, line)) return adjList;
    int rows = stoi(line);
    adjList.resize(rows);

    int row = 0;
    while (getline(file_in, line) && row < rows) {
        vector<int> neighbors;
        int col = 0;
        for (char c : line) {
            if (isspace(c)) continue;
            if (c == '1') neighbors.push_back(col);
            col++;
        }
        adjList[row] = neighbors;
        row++;
    }
    file_in.close();
    return adjList;
}

vector<vector<int>> convertListToMatrix(const string &filename) {
    ifstream file_in(filename);
    vector<vector<int>> adjMatrix;

    if (!file_in.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return adjMatrix;
    }

    string line;
    if (!getline(file_in, line)) return adjMatrix;
    int rows = stoi(line);
    adjMatrix.assign(rows, vector<int>(rows, 0));
    int row = 0;

    while(getline(file_in, line) && row < rows){
        for(int i = 1; i < line.size(); i++){
            if(isspace(line[i])) continue;
            int index = line[i] - '0';
            adjMatrix[row][index] = 1;
        }

        row++;
    }

    file_in.close();
    return adjMatrix;
}


bool isDirected(const vector<vector<int>> &adjMatrix) {
    int n = adjMatrix.size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (adjMatrix[i][j] != adjMatrix[j][i]) return true;
        }
    }
    return false;
}

int countVertices(const vector<vector<int>> &adjMatrix){
    return adjMatrix.size();
}


int countEdges(const vector<vector<int>> &adjMatrix){
    int rows = adjMatrix.size();
    int cols = adjMatrix[0].size();
    int ans = 0;
    bool directed = isDirected(adjMatrix);

    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            if(adjMatrix[i][j] == 1) ans++;
        }
    }

    if (!directed) ans /= 2;
    return ans;
}

vector<int> getIsolatedVertices(const vector<vector<int>> &adjMatrix){
    int rows = adjMatrix.size();
    int cols = adjMatrix[0].size();
    vector<int> ans;

    for(int i = 0; i < rows; i++){
        bool isolated = true;
        for(int j = 0; j < cols; j++){
            if(adjMatrix[i][j] || adjMatrix[j][i]){
                isolated = false;
                break;
            }
        }
        if(isolated) ans.push_back(i);
    }
    return ans;
}

bool isCompleteGraph(const vector<vector<int>> &adjMatrix){
    int n = adjMatrix.size();
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(i != j && adjMatrix[i][j] == 0)
                return false;
        }
    }
    return true;
}

bool isBipartite(const vector<vector<int>> & adjMatrix){
    vector<vector<int>> graph = general(adjMatrix);
    vector<int> colors(graph.size(), 0);
    std::queue<int> queue;
    for(int i = 0; i < graph.size(); i++){
        if(!colors[i]){
            queue.push(i);
            colors[i] = 1;
            while(!queue.empty()){
                int node = queue.front();
                queue.pop();
                for(int neigh : graph[node]){
                    if(!colors[neigh]){
                        queue.push(neigh);
                        colors[neigh] = -colors[node];
                    }
                    else if(colors[neigh] == colors[node]) return false;
                }
            }
        }
    }
    return true;
}

bool isCompleteBipartite(const vector<vector<int>> &adjMatrix){
    vector<vector<int>> graph = general(adjMatrix);
    vector<int> colors(graph.size(), 0);
    vector<int> partA, partB;
    queue<int> queue;
    for(int i = 0; i < graph.size(); i++){
        if(!colors[i]){
            queue.push(i);
            colors[i] = 1;
            partA.push_back(i);
            while(!queue.empty()){
                int node = queue.front(); queue.pop();
                for(int neigh : graph[node]){
                    if(!colors[neigh]){
                        queue.push(neigh);
                        colors[neigh] = -colors[node];
                        if(colors[neigh] == 1) partA.push_back(neigh);
                        else partB.push_back(neigh);
                    }
                    else if(colors[neigh] == colors[node]) return false;
                }
            }
        }
    }
    // Check partA
    for(int u : partA){
        if(graph[u].size() != partB.size()) return false;
        for(int v : graph[u]){
            if(colors[v] != -1) return false;
        }
    }
    // Check partB
    for(int u : partB){
        if(graph[u].size() != partA.size()) return false;
        for(int v : graph[u]){
            if(colors[v] != 1) return false;
        }
    }
    return true;
}

vector<vector<int>> convertToUndirectedGraph(const vector<vector<int>>& adjMatrix){
    int rows = adjMatrix.size();
    int cols = adjMatrix[0].size();
    vector<vector<int>> undirected_graph(rows, vector<int>(cols, 0));
    for(int i = 0; i<rows; i++){
        for(int j = 0; j<cols; j++){
            if(adjMatrix[i][j]){
                undirected_graph[i][j] = 1;
                undirected_graph[j][i] = 1;
            }
        }
    }

    return undirected_graph;
}


vector<vector<int>> dfsSpanningTree(const vector<vector<int>> &adjMatrix, int start){
    int n = adjMatrix.size();
    vector<vector<int>> res(n, vector<int> (n, 0));
    vector<bool> visited(n, false);
    stack<int> s;
    s.push(start);
    visited[start] = true;

    while (!s.empty()) {
        int node = s.top(); s.pop();
        for (int neigh = 0; neigh < n; ++neigh) {
            if (adjMatrix[node][neigh] && !visited[neigh]) {
                visited[neigh] = true;
                res[node][neigh] = 1;
                res[neigh][node] = 1;
                s.push(neigh);
            }
        }
    }
    return res;
}

vector<vector<int>> bfsSpanningTree(const vector<vector<int>> &adjMatrix, int start){
    int n = adjMatrix.size();
    vector<vector<int>> res(n, vector<int>(n, 0));
    vector<bool> visited(n, false);
    queue<int> q;
    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
        int node = q.front(); q.pop();
        for (int neigh = 0; neigh < n; ++neigh) {
            if (adjMatrix[node][neigh] && !visited[neigh]) {
                visited[neigh] = true;
                res[node][neigh] = 1;
                res[neigh][node] = 1;
                q.push(neigh);
            }
        }
    }

    return res;
}



vector<vector<int>> getComplementGraph(const vector<vector<int>> &adjMatrix){
    int n = adjMatrix.size();
    vector<vector<int>> complement(n, vector<int>(n, 0));

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(i != j) complement[i][j] = adjMatrix[i][j] ? 0 : 1;
        }
    }
    return complement;
}


vector<int> Euler_Undirected(vector<vector<int>> adjMatrix, int start) {
    int n = adjMatrix.size();
    stack<int> path;
    vector<int> circuit;
    path.push(start);

    while (!path.empty()) {
        int node = path.top();
        bool found = false;

        for (int i = 0; i < n; i++) {
            if (adjMatrix[node][i] > 0) {
                adjMatrix[node][i] = 0;
                adjMatrix[i][node] = 0;
                path.push(i);
                found = true;
                break;
            }
        }

        if (!found) {
            circuit.push_back(node);
            path.pop();
        }
    }

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (adjMatrix[i][j] != 0)
                return {};

    reverse(circuit.begin(), circuit.end());
    return circuit;
}



vector<int> Euler_Directed(vector<vector<int>> adjMatrix, int start) {
    int n = adjMatrix.size();
    stack<int> path;
    vector<int> circuit;
    path.push(start);

    while (!path.empty()) {
        int node = path.top();
        bool found = false;

        for (int i = 0; i < n; i++) {
            if (adjMatrix[node][i] > 0) {
                adjMatrix[node][i] = 0;
                path.push(i);
                found = true;
                break;
            }
        }

        if (!found) {
            circuit.push_back(node);
            path.pop();
        }
    }

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (adjMatrix[i][j] != 0)
                return {};

    reverse(circuit.begin(), circuit.end());
    return circuit;
}

bool hasEulerCycleUndirected(const vector<vector<int>>& adjMatrix) {
    int n = adjMatrix.size();
    vector<bool> visited(n, false);
    int start = -1;
    for (int i = 0; i < n; ++i) {
        int deg = 0;
        for (int j = 0; j < n; ++j) deg += adjMatrix[i][j];
        if (deg > 0) {
            start = i;
            break;
        }
    }
    if (start == -1) return false;

    stack<int> s;
    s.push(start);
    visited[start] = true;
    while (!s.empty()) {
        int u = s.top(); s.pop();
        for (int v = 0; v < n; ++v) {
            if (adjMatrix[u][v] && !visited[v]) {
                visited[v] = true;
                s.push(v);
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        int deg = 0;
        for (int j = 0; j < n; ++j) deg += adjMatrix[i][j];
        if (deg > 0 && !visited[i]) return false;
    }

    for (int i = 0; i < n; ++i) {
        int deg = 0;
        for (int j = 0; j < n; ++j) deg += adjMatrix[i][j];
        if (deg % 2 != 0) return false;
    }
    return true;
}

bool hasEulerCycleDirected(const vector<vector<int>>& adjMatrix) {
    int n = adjMatrix.size();
    vector<int> in_deg(n, 0), out_deg(n, 0);

    for (int u = 0; u < n; ++u)
        for (int v = 0; v < n; ++v)
            if (adjMatrix[u][v]) {
                out_deg[u]++;
                in_deg[v]++;
            }
    for (int i = 0; i < n; ++i)
        if (in_deg[i] != out_deg[i]) return false;

    vector<vector<int>> undirected(n, vector<int>(n, 0));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (adjMatrix[i][j] || adjMatrix[j][i])
                undirected[i][j] = undirected[j][i] = 1;

    vector<bool> visited(n, false);
    int start = -1;
    for (int i = 0; i < n; ++i)
        if (out_deg[i] > 0) { start = i; break; }
    if (start == -1) return false;

    stack<int> s;
    s.push(start);
    visited[start] = true;
    while (!s.empty()) {
        int u = s.top(); s.pop();
        for (int v = 0; v < n; ++v)
            if (undirected[u][v] && !visited[v]) {
                visited[v] = true;
                s.push(v);
            }
    }
    for (int i = 0; i < n; ++i)
        if (out_deg[i] > 0 && !visited[i]) return false;

    return true;
}


bool hasEulerCycle(const vector<vector<int>>& adjMatrix) {
    if (isDirected(adjMatrix)) return hasEulerCycleDirected(adjMatrix);
    else return hasEulerCycleUndirected(adjMatrix);
}

vector<int> findEulerCycle(const vector<vector<int>>& adjMatrix){
    if (!hasEulerCycle(adjMatrix)) return {};


    if(isDirected(adjMatrix)) return Euler_Directed(adjMatrix, 0);

    return Euler_Undirected(adjMatrix, 0);
}

vector<int> dijkstra(int start, int end, const vector<vector<int>>& adjMatrix) {
    int n = adjMatrix.size();
    vector<int> distance(n, INT_MAX);
    vector<int> prev(n, -1);
    vector<bool> visited(n, false);

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    pq.push({0, start});
    distance[start] = 0;

    while (!pq.empty()) {
        auto [dist_u, u] = pq.top(); pq.pop();

        if (visited[u]) continue;
        visited[u] = true;

        if (u == end) break;    

        for (int v = 0; v < n; ++v) {
            if (adjMatrix[u][v] == 0 || u == v) continue;

            int new_dist = distance[u] + adjMatrix[u][v];
            if (new_dist < distance[v]) {
                distance[v] = new_dist;
                prev[v] = u;
                pq.push({new_dist, v});
            }
        }
    }

    vector<int> path;
    if (distance[end] == INT_MAX) return path;

    for (int at = end; at != -1; at = prev[at]) {
        path.push_back(at);
    }
    reverse(path.begin(), path.end());
    return path;
}

vector<int> bellmanFord(int start, int end, const vector<vector<int>>& adjMatrix) {
    int n = adjMatrix.size();
    vector<int> distance(n, INT_MAX);
    vector<int> prev(n, -1);

    distance[start] = 0;

    for (int i = 0; i < n - 1; ++i) {
        for (int u = 0; u < n; ++u) {
            for (int v = 0; v < n; ++v) {
                if (adjMatrix[u][v] != 0 && distance[u] != INT_MAX) {
                    int weight = adjMatrix[u][v];
                    if (distance[u] + weight < distance[v]) {
                        distance[v] = distance[u] + weight;
                        prev[v] = u;
                    }
                }
            }
        }
    }

    // Check for negative-weight cycles
    for (int u = 0; u < n; ++u) {
        for (int v = 0; v < n; ++v) {
            if (adjMatrix[u][v] != 0 && distance[u] != INT_MAX) {
                int weight = adjMatrix[u][v];
                if (distance[u] + weight < distance[v]) {
                    // Negative cycle detected
                    return {};
                }
            }
        }
    }

    vector<int> path;
    if (distance[end] == INT_MAX) return path;

    for (int at = end; at != -1; at = prev[at]) {
        path.push_back(at);
    }
    reverse(path.begin(), path.end());
    return path;
}
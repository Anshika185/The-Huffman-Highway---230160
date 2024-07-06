#include <iostream>
#include <vector>
#include <list>

using namespace std;

class Graph {
    int V;  // Number of vertices
    list<int> *adj;  // Pointer to an array containing adjacency lists

    void findAllPathsUtil(int u, int v, vector<bool> &visited, vector<int> &path);

public:
    Graph(int V);  // Constructor
    void addEdge(int u, int v);
    void findAllPaths(int u, int v);
};

Graph::Graph(int V) {
    this->V = V;
    adj = new list<int>[V];
}

void Graph::addEdge(int u, int v) {
    adj[u].push_back(v);  // Add v to u’s list.
}

void Graph::findAllPathsUtil(int u, int v, vector<bool> &visited, vector<int> &path) {
    visited[u] = true;
    path.push_back(u);

    if (u == v) {
        for (int i = 0; i < path.size(); i++)
            cout << path[i] << " ";
        cout << endl;
    } else {
        for (auto i = adj[u].begin(); i != adj[u].end(); ++i)
            if (!visited[*i])
                findAllPathsUtil(*i, v, visited, path);
    }

    path.pop_back();
    visited[u] = false;
}

void Graph::findAllPaths(int u, int v) {
    vector<bool> visited(V, false);
    vector<int> path;
    findAllPathsUtil(u, v, visited, path);
}

int main() {
    int V, E;
    cout << "Enter the number of vertices: ";
    cin >> V;
    cout << "Enter the number of edges: ";
    cin >> E;

    Graph g(V);

    cout << "Enter the edges (u v):\n";
    for (int i = 0; i < E; i++) {
        int u, v;
        cin >> u >> v;
        g.addEdge(u, v);
    }

    int start, end;
    cout << "Enter the start node: ";
    cin >> start;
    cout << "Enter the end node: ";
    cin >> end;

    cout << "Following are all different paths from " << start << " to " << end << ":\n";
    g.findAllPaths(start, end);

    return 0;
}

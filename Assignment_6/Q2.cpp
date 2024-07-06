#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

bool is_hamiltonian_path(vector<vector<int>>& graph, vector<int>& path, vector<bool>& visited, int pos, int n) {
    // If all vertices are included in the path
    if (pos == n) {
        return true;
    }

    for (int v = 0; v < n; ++v) {
        if (graph[path[pos - 1]][v] == 1 && !visited[v]) {
            visited[v] = true;
            path[pos] = v;
            if (is_hamiltonian_path(graph, path, visited, pos + 1, n)) {
                return true;
            }
            visited[v] = false;
        }
    }
    return false;
}

bool is_hamiltonian_circuit(vector<vector<int>>& graph, vector<int>& path, vector<bool>& visited, int n) {
    if (is_hamiltonian_path(graph, path, visited, 1, n)) {
        if (graph[path[n - 1]][path[0]] == 1) {
            return true;
        }
    }
    return false;
}

void find_hamiltonian_path_and_circuit(vector<vector<int>>& graph) {
    int n = graph.size();
    vector<int> path(n, -1);
    vector<bool> visited(n, false);

    for (int i = 0; i < n; ++i) {
        path[0] = i;
        visited[i] = true;
        if (is_hamiltonian_path(graph, path, visited, 1, n)) {
            cout << "Hamiltonian Path exists starting at vertex: " << i << endl;
            cout << "Path: ";
            for (int j = 0; j < n; ++j) {
                cout << path[j] << " ";
            }
            cout << endl;
            if (is_hamiltonian_circuit(graph, path, visited, n)) {
                cout << "Hamiltonian Circuit exists starting and ending at vertex: " << i << endl;
            } else {
                cout << "Hamiltonian Circuit does not exist." << endl;
            }
            return;
        }
        visited[i] = false;
    }

    cout << "No Hamiltonian Path or Circuit exists." << endl;
}

int main() {
    int n;
    cout << "Enter the number of vertices in the graph: ";
    cin >> n;

    vector<vector<int>> graph(n, vector<int>(n));

    cout << "Enter the adjacency matrix (" << n << "x" << n << "):\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> graph[i][j];
        }
    }

    find_hamiltonian_path_and_circuit(graph);

    return 0;
}

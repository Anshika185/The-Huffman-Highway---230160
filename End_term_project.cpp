#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>
#include <limits>
#include <utility>
#include <queue>
#include <algorithm>

using namespace std;

// Structure to represent a node in the graph
struct Node {
    string name;
    int x, y;
    Node(string name, int x, int y) : name(name), x(x), y(y) {}
};

// Structure to represent the graph
class Graph {
public:
    // Adjacency list to store the graph
    unordered_map<string, vector<pair<string, int>>> adjList;

    // Add an edge to the graph
    void addEdge(const string& from, const string& to, int distance) {
        adjList[from].push_back(make_pair(to, distance));
        adjList[to].push_back(make_pair(from, distance)); // Because the graph is undirected
    }

    // Dijkstra's algorithm to find the shortest path
    vector<string> dijkstra(const string& start, const string& end) {
        unordered_map<string, int> distances;
        unordered_map<string, string> previous;
        set<pair<int, string>> nodes;

        for (const auto& pair : adjList) {
            if (pair.first == start) {
                distances[pair.first] = 0;
                nodes.insert(make_pair(0, pair.first));
            } else {
                distances[pair.first] = numeric_limits<int>::max();
                nodes.insert(make_pair(numeric_limits<int>::max(), pair.first));
            }
        }

        while (!nodes.empty()) {
            auto smallest = *nodes.begin();
            nodes.erase(nodes.begin());

            if (smallest.second == end) {
                vector<string> path;
                while (previous.find(smallest.second) != previous.end()) {
                    path.push_back(smallest.second);
                    smallest.second = previous[smallest.second];
                }
                path.push_back(start);
                reverse(path.begin(), path.end());
                return path;
            }

            if (distances[smallest.second] == numeric_limits<int>::max()) {
                break;
            }

            for (const auto& neighbor : adjList[smallest.second]) {
                int alt = distances[smallest.second] + neighbor.second;
                if (alt < distances[neighbor.first]) {
                    nodes.erase(make_pair(distances[neighbor.first], neighbor.first));
                    distances[neighbor.first] = alt;
                    previous[neighbor.first] = smallest.second;
                    nodes.insert(make_pair(alt, neighbor.first));
                }
            }
        }

        return {};
    }
};

int main() {
    // Create the graph
    Graph graph;

    // Add nodes and edges
    graph.addEdge("Hall 11", "Events Ground", 160);
    graph.addEdge("Events Ground", "Pronite Ground", 160);
    graph.addEdge("Pronite Ground", "New Shopping Complex", 80);
    graph.addEdge("New Shopping Complex", "Health Centre", 300);
    graph.addEdge("Health Centre", "Hall 6", 100);
    graph.addEdge("Hall 10", "Hall 11", 200);
    graph.addEdge("Hall 9", "Hall 10", 180);
    graph.addEdge("Hall 13", "Hall 9", 280);
    graph.addEdge("Hall 12", "Hall 13", 150);
    graph.addEdge("Hall 2", "Hall 12", 180);
    graph.addEdge("Girls Hostel 1", "Hall 2", 250);
    graph.addEdge("Kargil Chowk", "Girls Hostel 1", 250);
    graph.addEdge("Hall 1", "Hall 5", 75);
    graph.addEdge("Hall 1", "Hall 2", 170);
    graph.addEdge("Hall 3", "Hall 1", 175);
    graph.addEdge("Hall 4", "Hall 3", 100);
    graph.addEdge("Hall 4", "Hall 7", 243);
    graph.addEdge("Hall 5", "Hall 1", 75);
    graph.addEdge("Hall 5", "Hall 7", 88);
    graph.addEdge("Open Air Theatre", "Hall 8", 80);
    graph.addEdge("Hall 8", "Hall 7", 30);
    graph.addEdge("Hall 9", "Hall 5", 70);
    graph.addEdge("Hall 7", "Pronite Ground", 160);
    graph.addEdge("Pronite Ground", "New Shopping Complex", 80);
    graph.addEdge("New Shopping Complex", "Health Centre", 300);
    graph.addEdge("Health Centre", "Counselling Service", 140);
    graph.addEdge("Counselling Service", "Kargil Chowk", 250);
    graph.addEdge("Kargil Chowk", "Girls Hostel 1", 250);

    // Get user input for start and end locations
    string start, end;
    cout << "Enter start location: ";
    getline(cin, start);
    cout << "Enter end location: ";
    getline(cin, end);

    // Find the shortest path between the user-specified nodes
    vector<string> path = graph.dijkstra(start, end);

    // Print the path
    if (!path.empty()) {
        cout << "Shortest path from " << start << " to " << end << ": ";
        for (const auto& node : path) {
            cout << node << " ";
        }
        cout << endl;
    } else {
        cout << "No path found from " << start << " to " << end << "." << endl;
    }

    return 0;
}

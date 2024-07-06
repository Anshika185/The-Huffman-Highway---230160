#include <iostream>
#include <vector>
#include <queue>
#include <tuple>

using namespace std;

// Directions for moving in 6 possible ways: up, down, left, right, forward, backward
int directions[6][3] = {
    {1, 0, 0}, {-1, 0, 0}, 
    {0, 1, 0}, {0, -1, 0}, 
    {0, 0, 1}, {0, 0, -1}
};

struct Node {
    int x, y, z, dist;
    Node(int _x, int _y, int _z, int _dist) : x(_x), y(_y), z(_z), dist(_dist) {}
};

int shortest_path_3d(int X, int Y, int Z, int xs, int ys, int zs, int xd, int yd, int zd, vector<vector<vector<int>>> &grid) {
    // Check if the start or end points are blocked
    if (grid[xs][ys][zs] == 1 || grid[xd][yd][zd] == 1) {
        return -1;
    }

    queue<Node> q;
    q.push(Node(xs, ys, zs, 0));
    vector<vector<vector<bool>>> visited(X, vector<vector<bool>>(Y, vector<bool>(Z, false)));
    visited[xs][ys][zs] = true;

    while (!q.empty()) {
        Node current = q.front();
        q.pop();

        // Check if we reached the destination
        if (current.x == xd && current.y == yd && current.z == zd) {
            return current.dist;
        }

        // Explore neighbors
        for (auto dir : directions) {
            int nx = current.x + dir[0];
            int ny = current.y + dir[1];
            int nz = current.z + dir[2];

            if (nx >= 0 && nx < X && ny >= 0 && ny < Y && nz >= 0 && nz < Z && 
                grid[nx][ny][nz] == 0 && !visited[nx][ny][nz]) {
                visited[nx][ny][nz] = true;
                q.push(Node(nx, ny, nz, current.dist + 1));
            }
        }
    }

    // If we exhaust the queue without finding the destination
    return -1;
}

int main() {
    int X, Y, Z;
    cin >> X >> Y >> Z;

    int xs, ys, zs, xd, yd, zd;
    cin >> xs >> ys >> zs >> xd >> yd >> zd;

    vector<vector<vector<int>>> grid(X, vector<vector<int>>(Y, vector<int>(Z)));

    for (int x = 0; x < X; ++x) {
        for (int y = 0; y < Y; ++y) {
            for (int z = 0; z < Z; ++z) {
                cin >> grid[x][y][z];
            }
        }
    }

    int result = shortest_path_3d(X, Y, Z, xs, ys, zs, xd, yd, zd, grid);
    cout << result << endl;

    return 0;
}

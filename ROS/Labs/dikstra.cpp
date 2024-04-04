#include <vector>
#include <queue>
#include <iostream>

using namespace std;

struct Node {
  int x, y;
  int distance;
  bool visited;

  Node(int x, int y, int distance) : x(x), y(y), distance(distance), visited(false) {}
};

struct NodeComparator {
  bool operator()(const Node& a, const Node& b) {
    return a.distance > b.distance;
  }
};

int shortestPath(vector<vector<int>>& grid, int startX, int startY, int endX, int endY) {
  if (grid[startX][startY] == 1 || grid[endX][endY] == 1) {
    return -1;
  }

  int n = grid.size();
  int m = grid[0].size();

  vector<vector<bool>> visited(n, vector<bool>(m, false));
  priority_queue<Node, vector<Node>, NodeComparator> pq;

  pq.push(Node(startX, startY, 0));

  while (!pq.empty()) {
    Node currentNode = pq.top();
    pq.pop();

    if (currentNode.x == endX && currentNode.y == endY) {
      return currentNode.distance;
    }

    visited[currentNode.x][currentNode.y] = true;

    for (int dx = -1; dx <= 1; dx++) {
      for (int dy = -1; dy <= 1; dy++) {
        if (dx == 0 && dy == 0) {
          continue;
        }

        int newX = currentNode.x + dx;
        int newY = currentNode.y + dy;

        if (newX >= 0 && newX < n && newY >= 0 && newY < m && grid[newX][newY] != 1 && !visited[newX][newY]) {
          int newDistance = currentNode.distance + 1;
          pq.push(Node(newX, newY, newDistance));
        }
      }
    }
  }

  return -1;
}

int main() {
  vector<vector<int>> grid = {
    {0, 0, 0, 0, 0},
    {0, 1, 1, 1, 0},
    {0, 0, 0, 0, 0},
    {0, 1, 0, 0, 1},
    {0, 0, 0, 0, 0},
  };

  int startX = 0, startY = 0;
  int endX = 4, endY = 4;

  int shortestPathLength = shortestPath(grid, startX, startY, endX, endY);

  if (shortestPathLength == -1) {
    cout << "No path found" << endl;
  } else {
    cout << "Shortest path length: " << shortestPathLength << endl;
  }

  return 0;
}

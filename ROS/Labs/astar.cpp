#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <limits>
#include <algorithm>
#include <set>
using namespace std;

struct Cell {
    int row, col;
    int g, h; // g: Cost from the start, h: Heuristic distance
    Cell* parent;

    Cell(int r, int c, int g_cost, int h_cost, Cell* p) : row(r), col(c), g(g_cost), h(h_cost), parent(p) {}

    int cost() const { return g + h; }

    bool operator<(const Cell& other) const {
        return cost() > other.cost();
    }
};

// Calculate Manhattan distance heuristic
int manhattanDistance(pair<int, int> a, pair<int, int> b) {
    return abs(a.first - b.first) + abs(a.second - b.second);
}

vector<pair<int, int>> findPath(const vector<vector<int>>& grid, pair<int, int> start, pair<int, int> goal) {
    int rows = grid.size();
    int cols = grid[0].size();

    if (start.first < 0 || start.first >= rows || start.second < 0 || start.second >= cols ||
        goal.first < 0 || goal.first >= rows || goal.second < 0 || goal.second >= cols ||
        grid[start.first][start.second] == 1 || grid[goal.first][goal.second] == 1) {
        cout << "Invalid start or goal position." << endl;
        return {};
    }

    vector<pair<int, int>> directions = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}}; // Right, Down, Left, Up
    set<pair<int,int>> path_set;
    priority_queue<Cell> openCells;
    vector<vector<bool>> closed(rows, vector<bool>(cols, false));
    //Cell * cell = new Cell(start.first, start.second, 0, manhattanDistance(start, goal), nullptr);
    openCells.push(Cell(start.first, start.second, 0, manhattanDistance(start, goal), nullptr));
    closed[start.first][start.second] = true;

    while (!openCells.empty()) {
        Cell current = openCells.top();
        openCells.pop();

        if (current.row == goal.first && current.col == goal.second) {
            vector<pair<int, int>> path;
            for(auto& element : path_set)
            {
                path.push_back({element.first, element.second});

            }
             return path;
        }

        for (const auto& dir : directions) {
            int newRow = current.row + dir.first;
            int newCol = current.col + dir.second;

            if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols && grid[newRow][newCol] == 0 && !closed[newRow][newCol]) {
                int newG = current.g + 1;
                int newH = manhattanDistance({newRow, newCol}, goal);
                path_set.insert(make_pair(current.row, current.col));

                cout << "current " << current.row << " " << 
                current.col << endl;
                
                Cell * cell = new Cell(newRow, newCol, newG, newH, new Cell(current.row, current.col, 0, 0, nullptr));
                openCells.push(*cell);
                closed[newRow][newCol] = true;
            }
        }
    }

    cout << "No path found." << endl;
    return {};
}

int main() {
    vector<vector<int>> grid = {
        {0, 0, 0, 0, 1},
        {1, 1, 0, 1, 1},
        {0, 0, 0, 0, 0},
        {1, 1, 0, 1, 1},
        {0, 0, 0, 0, 0}
    };

    pair<int, int> start = {0, 0};
    pair<int, int> goal = {4, 4};

    vector<pair<int, int>> path = findPath(grid, start, goal);

    if (!path.empty()) {
        cout << "Path found:" << endl;
        for (const auto& p : path) {
            cout << "(" << p.first << ", " << p.second << ") ";
        }
        cout << endl;
    } else {
        cout << "No valid path exists." << endl;
    }

    return 0;
}

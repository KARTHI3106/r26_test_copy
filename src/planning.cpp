#include "planning.h"
#include <cmath>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>

using namespace std;

struct Node {
  int x, y;
  double f, g, h;
  pair<int, int> parent;
  
  Node(int x, int y, double g, double h, pair<int, int> parent = {-1, -1}) 
    : x(x), y(y), g(g), h(h), f(g + h), parent(parent) {}
  
  bool operator>(const Node& other) const {
    return f > other.f;
  }
};

Planner::Planner(const vector<vector<bool>> &grid) : grid(grid) {
  rows = grid.size();
  cols = grid[0].size();
}

bool Planner::isvalid(int x, int y) const {
  return (x >= 0 && x < rows && y >= 0 && y < cols && !grid[x][y]);
}

double Planner::heuristic(int x1, int y1, int x2, int y2) const {
  return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

vector<pair<int, int>> Planner::pathplanning(pair<int, int> start,
                                             pair<int, int> goal) {
  vector<pair<int, int>> path; // store final path 
  
  // A* algorithm implementation
  priority_queue<Node, vector<Node>, greater<Node>> openSet;
  map<pair<int, int>, double> gScore;
  map<pair<int, int>, pair<int, int>> cameFrom;
  
  // Directions: up, down, left, right, and diagonals
  vector<pair<int, int>> directions = {
    {-1, 0}, {1, 0}, {0, -1}, {0, 1},
    {-1, -1}, {-1, 1}, {1, -1}, {1, 1}
  };
  
  // Initialize
  gScore[start] = 0;
  double h = heuristic(start.first, start.second, goal.first, goal.second);
  openSet.push(Node(start.first, start.second, 0, h));
  
  while (!openSet.empty()) {
    Node current = openSet.top();
    openSet.pop();
    
    // If we reached the goal
    if (current.x == goal.first && current.y == goal.second) {
      // Reconstruct path
      pair<int, int> curr = {current.x, current.y};
      while (curr.first != -1 && curr.second != -1) {
        path.push_back(curr);
        if (cameFrom.find(curr) != cameFrom.end()) {
          curr = cameFrom[curr];
        } else {
          break;
        }
      }
      reverse(path.begin(), path.end());
      return path;
    }
    
    // Explore neighbors
    for (auto& dir : directions) {
      int newX = current.x + dir.first;
      int newY = current.y + dir.second;
      
      if (!isvalid(newX, newY)) continue;
      
      // Calculate movement cost (diagonal moves cost more)
      double moveCost = (abs(dir.first) + abs(dir.second) == 2) ? sqrt(2) : 1.0;
      double tentativeG = current.g + moveCost;
      
      pair<int, int> neighbor = {newX, newY};
      
      if (gScore.find(neighbor) == gScore.end() || tentativeG < gScore[neighbor]) {
        cameFrom[neighbor] = {current.x, current.y};
        gScore[neighbor] = tentativeG;
        double h = heuristic(newX, newY, goal.first, goal.second);
        openSet.push(Node(newX, newY, tentativeG, h));
      }
    }
  }
  
  return path; // Return empty if no path found
}

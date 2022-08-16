//
// Created by cjian on 8/8/2022.
//

#include "pMap.h"

#include <utility>
#include <cmath>
#include <unordered_set>

using std::unordered_set;
using std::unordered_map;
using std::priority_queue;
using std::pair;
typedef pair<int, int> int_p;

pMap::pMap() : pMap(100, 100, {}) {

}

pMap::pMap(int width, int height, std::vector<pObstacle> obstacles)
    : width(width), height(height), obstacle_list(std::move(obstacles)),
      obs_pix_map(vector<vector<bool>>(width, vector<bool>(height, false))),
      point_cost_map(vector<vector<pPoint>>(width, vector<pPoint>(height))) {
  reset_point_cost_map();

}

int get_dist(int x, int y) {
  return lround(sqrt(pow(x, 2.0f) + pow(y, 2.0f)));
}


void pMap::plot_obstacle(const pObstacle &obstacle, int bot_rad = 1) {
  int x = obstacle.x, y = obstacle.y, rad = obstacle.rad + bot_rad - 1;
  if (valid_x_y(x, y)) obs_pix_map[x][y] = true;
  for (int i = 0; i <= rad; ++i) {
    for (int j = 0; j <= rad; ++j) {
      auto dist = get_dist(i, j);
      if (dist <= rad) {
        if (valid_x_y(x - i, y - j)) obs_pix_map[x - i][y - j] = true;
        if (valid_x_y(x - i, y + j)) obs_pix_map[x - i][y + j] = true;
        if (valid_x_y(x + i, y - j)) obs_pix_map[x + i][y - j] = true;
        if (valid_x_y(x + i, y + j)) obs_pix_map[x + i][y + j] = true;
      }
    }
  }
}


bool pMap::valid_x_y(int x, int y) {
  // check if the x and y are within the obs_pix_map boundary and if it is already an obstacle
  return x >= 0 && x < width && y >= 0 && y < height && !obs_pix_map[x][y];
}

bool pMap::find_path(pPoint &start, pPoint &goal) {
  path.clear();
  reset_point_cost_map();
  std::unordered_map<pPoint, pPoint> cameFrom;
  start.cost = 0;
  point_cost_map[start.x][start.y].cost = 0;
  priority_queue<pPoint, vector<pPoint>, std::less<> > open_map;
  unordered_set<pPoint> open_set;
  open_map.push(start);
  open_set.insert(start);
  while (!open_map.empty()) {
    auto current = open_map.top();
    open_map.pop();
    open_set.erase(current);
    if (current == goal) {
      reconstruct_path(cameFrom, current);
      return true;
    }
    auto neighbors = get_neighbor(current);
    for (auto neighbor: neighbors) {
      auto tentative_cost = current.cost + 1;
      if (tentative_cost < neighbor->cost) {
        neighbor->cost = tentative_cost;
        cameFrom[*neighbor] = current;
        if (open_set.count(*neighbor) == 0) {
          open_map.push(*neighbor);
          open_set.insert(*neighbor);
        }
      }
    }
  }

  return false;
}

vector<pPoint *> pMap::get_neighbor(const pPoint &p) {
  vector<pPoint *> points;
  int x = p.x, y = p.y;
  if (valid_x_y(x - 1, y)) points.emplace_back(&point_cost_map[x - 1][y]);
  if (valid_x_y(x, y - 1)) points.emplace_back(&point_cost_map[x][y - 1]);
  if (valid_x_y(x + 1, y)) points.emplace_back(&point_cost_map[x + 1][y]);
  if (valid_x_y(x, y + 1)) points.emplace_back(&point_cost_map[x][y + 1]);
  return points;
}

void pMap::reconstruct_path(std::unordered_map<pPoint, pPoint> &camFrom, pPoint &current) {
  path = {current};
  while (camFrom.find(current) != camFrom.end()) {
    current = camFrom[current];
    path.push_back(current);
  }
  std::reverse(path.begin(), path.end());
}

void pMap::reset_point_cost_map() {
  for (int i = 0; i < width; ++i) {
    for (int j = 0; j < height; ++j) {
      point_cost_map[i][j] = pPoint(i,j);
    }
  }
}

void pMap::plot_obstacles( int bot_rad) {
  obs_pix_map = vector<vector<bool>>(width, vector<bool>(height, false));
  for (auto obs : obstacle_list){
    plot_obstacle(obs,bot_rad);
  }
}



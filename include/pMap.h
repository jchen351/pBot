//
// Created by cjian on 8/8/2022.
//

#ifndef PBOT_PMAP_H
#define PBOT_PMAP_H

#include "pObstacle.h"
#include <vector>
#include <queue>
#include <unordered_map>
#include <map>
#include  <functional>

using std::vector;
using std::queue;

struct pPoint {
  int x = 0;
  int y = 0;
  int cost = INT_MAX;
  pPoint() = default;
  pPoint(int x, int y): x(x), y(y), cost(INT_MAX){}
  friend bool operator==(const pPoint &lhs, const pPoint &rhs) { return rhs.x == lhs.x && rhs.y == lhs.y; }

  friend bool operator<(const pPoint &lhs, const pPoint &rhs) { return lhs.cost < rhs.cost; }


};
template<>
struct std::hash<pPoint>
{
  std::size_t operator()(pPoint const& s) const noexcept
  {
    std::size_t h1 = std::hash<int>{}(s.x);
    std::size_t h2 = std::hash<int>{}(s.y);
    return h1 ^ (h2 << 1); // or use boost::hash_combine
  }
};

struct pMap {
  pMap(int width, int height, std::vector<pObstacle> obstacles);

  pMap();


  int width;
  int height;
  std::vector<pObstacle> obstacles;
  vector<vector<bool> > pixMap;
  vector<vector<pPoint> > pointMap;
  void plot_obstacle(const pObstacle &obstacle, int bot_rad);

  bool valid_x_y(int x, int y);

  queue<pPoint> open_list;
  pPoint end_point, start_point;

  bool find_path(pPoint &start, pPoint &goal);
  vector<pPoint*> get_neighbor(const pPoint&);
  vector<pPoint> path;
  void reconstruct_path(std::unordered_map<pPoint, pPoint> &camFrom, pPoint& current);

};

#endif // PBOT_PMAP_H

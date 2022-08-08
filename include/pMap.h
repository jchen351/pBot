//
// Created by cjian on 8/8/2022.
//

#ifndef PBOT_PMAP_H
#define PBOT_PMAP_H
#include "pObstacle.h"
#include <vector>

struct pMap {
  pMap(int width, int height, std::vector<pObstacle> obstacles);
  pMap() = default;
  int width;
  int height;
  std::vector<pObstacle> obstacles;
};

#endif // PBOT_PMAP_H

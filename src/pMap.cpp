//
// Created by cjian on 8/8/2022.
//

#include "pMap.h"

#include <utility>
pMap::pMap(int width, int height, std::vector<pObstacle> obstacles)
    : width(width), height(height), obstacles(std::move(obstacles)) {}

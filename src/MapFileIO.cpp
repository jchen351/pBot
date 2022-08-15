//
// Created by cjian on 8/8/2022.
//
#include "MapFileIO.h"
#include <exception>
#include <fstream>
#include <iostream>
#include <sstream>

const std::string MapFileIO::file_suffix = "*.pmap";

pMap MapFileIO::load_map_from_file(const string &file_name) {
  if (!validate_file_name(file_name))
    throw std::exception("Invalid file suffix");

  ifstream file(file_name);

  string line;
  std::getline(file, line);
  istringstream iss(line);
  string w, h;
  getline(iss, w, ',');
  getline(iss, h, ',');
  int width = stoi(w);
  int height = stoi(h);
  pMap map(width,height,{});
  while (getline(file, line)) {
    istringstream iss1(line);
    string x, y, rad;
    getline(iss1, x, ',');
    getline(iss1, y, ',');
    getline(iss1, rad, ',');
    pObstacle obstacle = pObstacle(stoi(x), stoi(y), stoi(rad));
    map.obstacles.push_back(std::move(obstacle));
  }
  file.close();
  return map;
}
void MapFileIO::save_map_to_file(const pMap &map, const string &file_name) {
  if (!validate_file_name(file_name))
    throw std::exception("Invalid file suffix");
  ofstream file;
  file.open(file_name);
  file << map.width << ',' << map.height << '\n';
  for (const auto &obstacle : map.obstacles)
    file << obstacle.x << ',' << obstacle.y << ',' << obstacle.rad << '\n';
  file.close();
}
bool MapFileIO::validate_file_name(const string file_name) {
  return file_name.size() >= file_suffix.size() &&
         file_name.rfind(file_suffix.substr(1)) ==
             file_name.size() - file_suffix.size() + 1;
}

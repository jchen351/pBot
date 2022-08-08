//
// Created by cjian on 8/8/2022.
//

#ifndef PBOT_MAPFILEIO_H
#define PBOT_MAPFILEIO_H

#include "pMap.h"
#include <string>

using namespace std;
class MapFileIO {
public:
  static const string file_suffix;
  static pMap load_map_from_file(const string &file_name);
  static void save_map_to_file(const pMap &map, const string &file_name);
  static bool validate_file_name(string file_name);
};

#endif // PBOT_MAPFILEIO_H

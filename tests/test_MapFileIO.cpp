//
// Created by cjian on 8/8/2022.
//
#include "MapFileIO.h"
#include "gtest/gtest.h"
class MapFileIoTest : public ::testing::Test {
public:
  string fname = "test.pmap";
  pMap test_map = {25, 35, {{2, 3, 4}, {5, 6, 7}}};

protected:
  void SetUp() override { MapFileIO::save_map_to_file(test_map, fname); }
  void TearDown() override { remove(fname.c_str()); }
};

TEST_F(MapFileIoTest, valid_file_name) {
  ASSERT_TRUE(MapFileIO::validate_file_name("f.pmap"));
  ASSERT_TRUE(MapFileIO::validate_file_name("fff.pmap"));
  ASSERT_FALSE(MapFileIO::validate_file_name(".pmap"));
  ASSERT_FALSE(MapFileIO::validate_file_name("fff.pixMap"));
}
TEST_F(MapFileIoTest, load_map_from_file) {

  auto map = MapFileIO::load_map_from_file(fname);
  ASSERT_EQ(map.width, test_map.width);
  ASSERT_EQ(map.height, test_map.height);
  ASSERT_EQ(map.obstacles.size(), test_map.obstacles.size());
  for (int i = 0; i < map.obstacles.size(); i++) {
    ASSERT_EQ(map.obstacles[i].x, test_map.obstacles[i].x);
    ASSERT_EQ(map.obstacles[i].y, test_map.obstacles[i].y);
    ASSERT_EQ(map.obstacles[i].rad, test_map.obstacles[i].rad);
  }
}
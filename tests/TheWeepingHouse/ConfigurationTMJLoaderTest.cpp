
#include <gtest/gtest.h>

#include <TheWeepingHouse/ConfigurationTMJLoader.hpp>


#define TEST_FIXTURE_FILENAME "/Users/markoates/Repos/TheWeepingHouse/tests/test_fixtures/test-configuration.tmj"



TEST(TheWeepingHouse_ConfigurationTMJLoaderTest, can_be_created_without_blowing_up)
{
   TheWeepingHouse::ConfigurationTMJLoader configuration_tmj_loader;
}


TEST(TheWeepingHouse_ConfigurationTMJLoaderTest, load__does_not_blow_up)
{
   TheWeepingHouse::ConfigurationTMJLoader configuration_tmj_loader(TEST_FIXTURE_FILENAME);
   EXPECT_EQ(true, configuration_tmj_loader.load());
}


TEST(TheWeepingHouse_ConfigurationTMJLoaderTest, load__will_extract_the_dimentions)
{
   TheWeepingHouse::ConfigurationTMJLoader configuration_tmj_loader(TEST_FIXTURE_FILENAME);
   configuration_tmj_loader.load();
   EXPECT_EQ(1920, configuration_tmj_loader.get_tile_width());
   EXPECT_EQ(1080, configuration_tmj_loader.get_tile_height());
   EXPECT_EQ(1, configuration_tmj_loader.get_num_rows());
   EXPECT_EQ(1, configuration_tmj_loader.get_num_columns());
}


TEST(TheWeepingHouse_ConfigurationTMJLoaderTest, load__will_extract_the_objects)
{
   TheWeepingHouse::ConfigurationTMJLoader configuration_tmj_loader(TEST_FIXTURE_FILENAME);
   configuration_tmj_loader.load();

   std::vector<TheWeepingHouse::ConfigurationTMJLoaderElements::Object> objects =
      configuration_tmj_loader.get_objects();

   ASSERT_EQ(4, objects.size());

   EXPECT_EQ("hitspot", objects[0].get_type());
   EXPECT_EQ(115, objects[0].get_x());
   EXPECT_EQ(388, objects[0].get_y());
   EXPECT_EQ(115, objects[0].get_w());
   EXPECT_EQ(399, objects[0].get_h());
}



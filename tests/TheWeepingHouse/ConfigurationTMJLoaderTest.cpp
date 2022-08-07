
#include <gtest/gtest.h>

#include <TheWeepingHouse/ConfigurationTMJLoader.hpp>


TEST(TheWeepingHouse_ConfigurationTMJLoaderTest, can_be_created_without_blowing_up)
{
   TheWeepingHouse::ConfigurationTMJLoader configuration_tmjloader;
}


TEST(TheWeepingHouse_ConfigurationTMJLoaderTest, load__does_not_blow_up)
{
   TheWeepingHouse::ConfigurationTMJLoader configuration_tmjloader;
   EXPECT_EQ(true, configuration_tmjloader.load());
}


TEST(TheWeepingHouse_ConfigurationTMJLoaderTest, objects__contains_the_extracted_objects)
{
   TheWeepingHouse::ConfigurationTMJLoader configuration_tmjloader;
   configuration_tmjloader.load();
   // TODO
   //configuration_tmjloader.get_objects();
   //SUCCEED();
}



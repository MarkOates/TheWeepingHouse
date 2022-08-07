
#include <gtest/gtest.h>

#include <TheWeepingHouse/ConfigurationTMJLoader.hpp>


TEST(TheWeepingHouse_ConfigurationTMJLoaderTest, can_be_created_without_blowing_up)
{
   TheWeepingHouse::ConfigurationTMJLoader configuration_tmjloader;
}


TEST(TheWeepingHouse_ConfigurationTMJLoaderTest, load__does_not_blow_up)
{
   TheWeepingHouse::ConfigurationTMJLoader configuration_tmjloader;
   configuration_tmjloader.load();
   SUCCEED();
}


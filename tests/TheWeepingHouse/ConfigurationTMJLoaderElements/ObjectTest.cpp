
#include <gtest/gtest.h>

#include <TheWeepingHouse/ConfigurationTMJLoaderElements/Object.hpp>


TEST(TheWeepingHouse_ConfigurationTMJLoaderElements_ObjectTest, can_be_created_without_blowing_up)
{
   TheWeepingHouse::ConfigurationTMJLoaderElements::Object object;
}


TEST(TheWeepingHouse_ConfigurationTMJLoaderElements_ObjectTest, run__returns_the_expected_response)
{
   TheWeepingHouse::ConfigurationTMJLoaderElements::Object object;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, object.run());
}


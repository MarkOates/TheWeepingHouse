
#include <gtest/gtest.h>

#include <TheWeepingHouse/Shaders/FlatColor.hpp>


TEST(TheWeepingHouse_Shaders_FlatColorTest, can_be_created_without_blowing_up)
{
   TheWeepingHouse::Shaders::FlatColor flat_color;
}


TEST(TheWeepingHouse_Shaders_FlatColorTest, run__returns_the_expected_response)
{
   TheWeepingHouse::Shaders::FlatColor flat_color;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, flat_color.run());
}


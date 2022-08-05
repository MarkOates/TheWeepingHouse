
#include <gtest/gtest.h>

#include <TheWeepingHouse/Configurations/Primary.hpp>


TEST(TheWeepingHouse_Configurations_PrimaryTest, can_be_created_without_blowing_up)
{
   TheWeepingHouse::Configurations::Primary primary;
}


TEST(TheWeepingHouse_Configurations_PrimaryTest, run__returns_the_expected_response)
{
   TheWeepingHouse::Configurations::Primary primary;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, primary.run());
}


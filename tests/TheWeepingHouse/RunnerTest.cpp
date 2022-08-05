
#include <gtest/gtest.h>

#include <TheWeepingHouse/Runner.hpp>


TEST(TheWeepingHouse_RunnerTest, can_be_created_without_blowing_up)
{
   TheWeepingHouse::Runner runner;
}


TEST(TheWeepingHouse_RunnerTest, run__returns_the_expected_response)
{
   TheWeepingHouse::Runner runner;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, runner.run());
}


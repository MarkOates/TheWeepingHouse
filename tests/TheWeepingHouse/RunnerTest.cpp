
#include <gtest/gtest.h>

#include <TheWeepingHouse/Runner.hpp>


TEST(TheWeepingHouse_RunnerTest, can_be_created_without_blowing_up)
{
   TheWeepingHouse::Runner runner;
}


TEST(TheWeepingHouse_RunnerTest, run__runs_the_program)
{
   TheWeepingHouse::Runner runner;
   //runner.run("test");
   runner.run("test");
   SUCCEED();
}



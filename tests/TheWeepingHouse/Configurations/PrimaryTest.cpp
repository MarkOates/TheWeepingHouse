
#include <gtest/gtest.h>

#include <TheWeepingHouse/Configurations/Primary.hpp>


TEST(TheWeepingHouse_Configurations_PrimaryTest, can_be_created_without_blowing_up)
{
   TheWeepingHouse::Configurations::Primary primary;
}


#include <TheWeepingHouse/Runner.hpp>

TEST(TheWeepingHouse_RunnerTest, run__runs_the_program)
{
   TheWeepingHouse::Runner runner;
   runner.run("test");
   SUCCEED();
}



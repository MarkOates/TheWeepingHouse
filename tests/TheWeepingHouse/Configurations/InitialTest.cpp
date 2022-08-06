
#include <gtest/gtest.h>

#include <TheWeepingHouse/Configurations/Initial.hpp>


TEST(TheWeepingHouse_Configurations_InitialTest, can_be_created_without_blowing_up)
{
   TheWeepingHouse::Configurations::Initial initial;
}


#include <TheWeepingHouse/Runner.hpp>

TEST(TheWeepingHouse_Configurations_InitialTest, INTERACTIVE__works_in_the_primary_program)
{
   TheWeepingHouse::Runner runner;
   runner.run("test");
   SUCCEED();
}



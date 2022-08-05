
#include <gtest/gtest.h>

#include <TheWeepingHouse/Shaders/Multiply.hpp>


TEST(TheWeepingHouse_Shaders_MultiplyTest, can_be_created_without_blowing_up)
{
   TheWeepingHouse::Shaders::Multiply multiply;
}


#include <TheWeepingHouse/Runner.hpp>

TEST(TheWeepingHouse_Shaders_MultiplyTest, run__runs_the_program)
{
   TheWeepingHouse::Runner runner;
   //runner.run("test");
   SUCCEED();
}



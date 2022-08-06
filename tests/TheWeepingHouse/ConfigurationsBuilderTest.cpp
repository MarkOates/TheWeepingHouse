
#include <gtest/gtest.h>

#include <TheWeepingHouse/ConfigurationsBuilder.hpp>

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>


class TheWeepingHouse_ConfigurationsBuilderTest : public ::testing::Test{};

class TheWeepingHouse_ConfigurationsBuilderWithAllegroRenderingFixtureTest
   : public AllegroFlare::Testing::WithAllegroRenderingFixture{};



TEST_F(TheWeepingHouse_ConfigurationsBuilderTest, can_be_created_without_blowing_up)
{
   TheWeepingHouse::ConfigurationsBuilder configurations_builder;
}


TEST_F(TheWeepingHouse_ConfigurationsBuilderWithAllegroRenderingFixtureTest, DISABLED__build__will_not_blow_up)
{
   AllegroFlare::BitmapBin bitmap_bin;
   AllegroFlare::FontBin font_bin;
   AllegroFlare::EventEmitter event_emitter;
   AllegroFlare::Prototypes::FixedRoom2D::EntityCollectionHelper entity_collection_helper__this_is_a_hack;

   TheWeepingHouse::ConfigurationsBuilder configurations_builder(
      &bitmap_bin,
      &font_bin,
      &event_emitter,
      &entity_collection_helper__this_is_a_hack);

   configurations_builder.build();
}



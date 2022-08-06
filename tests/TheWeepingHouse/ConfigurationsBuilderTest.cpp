
#include <gtest/gtest.h>

#include <TheWeepingHouse/ConfigurationsBuilder.hpp>

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>

#ifdef _WIN32
#define TEST_FIXTURE_FONTS_FOLDER "/msys64/home/Mark/Repos/TheWeepingHouse/bin/programs/data/fonts/"
#define TEST_FIXTURE_BITMAPS_FOLDER "/msys64/home/Mark/Repos/TheWeepingHouse/bin/programs/data/bitmaps/"
#else
#define TEST_FIXTURE_FONTS_FOLDER "/Users/markoates/Repos/TheWeepingHouse/bin/programs/data/fonts/"
#define TEST_FIXTURE_BITMAPS_FOLDER "/Users/markoates/Repos/TheWeepingHouse/bin/programs/data/bitmaps/"
#endif


class TheWeepingHouse_ConfigurationsBuilderTest : public ::testing::Test{};

class TheWeepingHouse_ConfigurationsBuilderWithAllegroRenderingFixtureTest
   : public AllegroFlare::Testing::WithAllegroRenderingFixture{};



TEST_F(TheWeepingHouse_ConfigurationsBuilderTest, can_be_created_without_blowing_up)
{
   TheWeepingHouse::ConfigurationsBuilder configurations_builder;
}


TEST_F(TheWeepingHouse_ConfigurationsBuilderWithAllegroRenderingFixtureTest, build__will_not_blow_up)
{
   AllegroFlare::BitmapBin &bitmap_bin = get_bitmap_bin_ref();
   AllegroFlare::FontBin &font_bin = get_font_bin_ref();
   AllegroFlare::EventEmitter event_emitter;
   AllegroFlare::Prototypes::FixedRoom2D::EntityCollectionHelper entity_collection_helper__this_is_a_hack;

   bitmap_bin.set_full_path(TEST_FIXTURE_BITMAPS_FOLDER);
   font_bin.set_full_path(TEST_FIXTURE_FONTS_FOLDER);

   TheWeepingHouse::ConfigurationsBuilder configurations_builder(
      &bitmap_bin,
      &font_bin,
      &event_emitter,
      &entity_collection_helper__this_is_a_hack);

   configurations_builder.build();
}



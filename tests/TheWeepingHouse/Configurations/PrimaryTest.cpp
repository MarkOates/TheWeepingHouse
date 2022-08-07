
#include <gtest/gtest.h>

#include <TheWeepingHouse/Configurations/Primary.hpp>

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>

#ifdef _WIN32
#define TEST_FIXTURE_FONTS_FOLDER "/msys64/home/Mark/Repos/TheWeepingHouse/tests/test_fixtures/"
#define TEST_FIXTURE_BITMAPS_FOLDER "/msys64/home/Mark/Repos/TheWeepingHouse/tests/test_fixtures/"
#define PRODUCTION_FONTS_FOLDER "/msys64/home/Mark/Repos/TheWeepingHouse/bin/programs/data/fonts/"
#define PRODUCTION_BITMAPS_FOLDER "/msys64/home/Mark/Repos/TheWeepingHouse/bin/programs/data/bitmaps/"
#else
#define TEST_FIXTURE_FONTS_FOLDER "/Users/markoates/Repos/TheWeepingHouse/tests/test_fixtures/"
#define TEST_FIXTURE_BITMAPS_FOLDER "/Users/markoates/Repos/TheWeepingHouse/tests/test_fixtures/"
#define PRODUCTION_FONTS_FOLDER "/Users/markoates/Repos/TheWeepingHouse/bin/programs/data/fonts/"
#define PRODUCTION_BITMAPS_FOLDER "/Users/markoates/Repos/TheWeepingHouse/bin/programs/data/bitmaps/"
#endif


class TheWeepingHouse_Configurations_PrimaryTest : public ::testing::Test{};

class TheWeepingHouse_Configurations_PrimaryWithAllegroRenderingFixtureTest
   : public AllegroFlare::Testing::WithAllegroRenderingFixture{};

class TheWeepingHouse_Configurations_PrimaryWithAllegroRenderingFixtureTest_WITH_ASSEMBLED_configurations_builder
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{
public:
   TheWeepingHouse::Configurations::Primary primary_builder;

private:
   virtual void SetUp() override
   {
      AllegroFlare::Testing::WithAllegroRenderingFixture::SetUp();

      AllegroFlare::BitmapBin &bitmap_bin = get_bitmap_bin_ref();
      AllegroFlare::FontBin &font_bin = get_font_bin_ref();
      AllegroFlare::EventEmitter event_emitter;
      AllegroFlare::Prototypes::FixedRoom2D::EntityCollectionHelper entity_collection_helper__this_is_a_hack;

      bitmap_bin.set_full_path(PRODUCTION_BITMAPS_FOLDER);
      font_bin.set_full_path(PRODUCTION_FONTS_FOLDER);

      primary_builder.set_bitmap_bin(&bitmap_bin);
      primary_builder.set_font_bin(&font_bin);
      primary_builder.set_event_emitter(&event_emitter);
      primary_builder.set_entity_collection_helper__this_is_a_hack(&entity_collection_helper__this_is_a_hack);
   }
};


TEST_F(TheWeepingHouse_Configurations_PrimaryTest, can_be_created_without_blowing_up)
{
   TheWeepingHouse::Configurations::Primary primary_builder;
}


TEST_F(TheWeepingHouse_Configurations_PrimaryWithAllegroRenderingFixtureTest_WITH_ASSEMBLED_configurations_builder,
   build__will_not_blow_up)
{
   primary_builder.build();
}


TEST_F(TheWeepingHouse_Configurations_PrimaryWithAllegroRenderingFixtureTest_WITH_ASSEMBLED_configurations_builder,
   DISABLED__assemble_room__will_add_a_room_to_the_configuration_with_the_expected_properties)
{
   AllegroFlare::BitmapBin &bitmap_bin = get_bitmap_bin_ref();
   bitmap_bin.set_full_path(TEST_FIXTURE_BITMAPS_FOLDER);

   primary_builder.assemble_room("my_test_room_name", "This is a test room");

   // creates a room
   ASSERT_EQ(true, primary_builder.room_exists("my_test_room_name"));
   EXPECT_NE(nullptr, primary_builder.get_room_dictionary()["my_test_room_name"]);

   // creates a background
   ASSERT_EQ(true, primary_builder.entity_exists("my_test_room_name_bg"));
   EXPECT_NE(nullptr, primary_builder.get_entity_dictionary()["my_test_room_name_bg"]);

   // creates an "observe_..." script for the background
   ASSERT_EQ(true, primary_builder.script_exists("observe_my_test_room_name"));
   ASSERT_EQ(1, primary_builder.get_script_dictionary()["observe_my_test_room_name"].get_lines().size());
   EXPECT_EQ(
      "DIALOG: This is a test room",
      primary_builder.get_script_dictionary()["observe_my_test_room_name"].get_lines()[0]
   );

   // an association exists for the background entity and the room
   EXPECT_EQ(true, primary_builder.entity_room_association_exists("my_test_room_name_bg", "my_test_room_name"));
}


TEST_F(TheWeepingHouse_Configurations_PrimaryWithAllegroRenderingFixtureTest_WITH_ASSEMBLED_configurations_builder,
   the_production_configuration_has_the_expected_elements)
{
   AllegroFlare::Prototypes::FixedRoom2D::Configuration configuration = primary_builder.build();
   EXPECT_EQ(1, configuration.get_room_dictionary().count("front_hallway"));
   //EXPECT_EQ("front_hallway", configuration.get_starting_in_room_identifier());
}




#include <TheWeepingHouse/Runner.hpp>

//TEST(TheWeepingHouse_Configurations_PrimaryTest, INTERACTIVE__works_in_the_runner)
//{
   //TheWeepingHouse::Runner runner;
   //runner.run("test");
   //SUCCEED();
//}


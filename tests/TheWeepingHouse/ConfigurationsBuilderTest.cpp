
#include <gtest/gtest.h>

#include <TheWeepingHouse/ConfigurationsBuilder.hpp>

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


class TheWeepingHouse_ConfigurationsBuilderTest : public ::testing::Test{};

class TheWeepingHouse_ConfigurationsBuilderWithAllegroRenderingFixtureTest
   : public AllegroFlare::Testing::WithAllegroRenderingFixture{};

class TheWeepingHouse_ConfigurationsBuilderWithAllegroRenderingFixtureTest_WITH_ASSEMBLED_configurations_builder
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{
public:
   TheWeepingHouse::ConfigurationsBuilder configurations_builder;

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

      configurations_builder.set_bitmap_bin(&bitmap_bin);
      configurations_builder.set_font_bin(&font_bin);
      configurations_builder.set_event_emitter(&event_emitter);
      configurations_builder.set_entity_collection_helper__this_is_a_hack(&entity_collection_helper__this_is_a_hack);
   }
};


TEST_F(TheWeepingHouse_ConfigurationsBuilderTest, can_be_created_without_blowing_up)
{
   TheWeepingHouse::ConfigurationsBuilder configurations_builder;
}


TEST_F(TheWeepingHouse_ConfigurationsBuilderWithAllegroRenderingFixtureTest_WITH_ASSEMBLED_configurations_builder,
   build__will_not_blow_up)
{
   configurations_builder.build();
}


TEST_F(TheWeepingHouse_ConfigurationsBuilderWithAllegroRenderingFixtureTest_WITH_ASSEMBLED_configurations_builder,
   room_exists__will_return_true_if_the_room_exists)
{
   // TODO: do not use "assemble_room" for this test
   configurations_builder.assemble_room("my_test_room_name", "This is a test room");
   EXPECT_EQ(true, configurations_builder.room_exists("my_test_room_name"));
}


TEST_F(TheWeepingHouse_ConfigurationsBuilderWithAllegroRenderingFixtureTest_WITH_ASSEMBLED_configurations_builder,
   room_exists__will_return_false_if_the_room_does_not_exist)
{
   EXPECT_EQ(false, configurations_builder.room_exists("a-room-that-does-not-exist"));
}


TEST_F(TheWeepingHouse_ConfigurationsBuilderWithAllegroRenderingFixtureTest_WITH_ASSEMBLED_configurations_builder,
   script_exists__will_return_true_if_the_script_is_present)
{
   // TODO: do not use "assemble_room" for this test
   configurations_builder.assemble_room("my_test_room_name", "This is a test room");
   EXPECT_EQ(true, configurations_builder.script_exists("observe_my_test_room_name"));
}


TEST_F(TheWeepingHouse_ConfigurationsBuilderWithAllegroRenderingFixtureTest_WITH_ASSEMBLED_configurations_builder,
   script_exists__will_return_false_if_the_script_is_not_present)
{
   EXPECT_EQ(false, configurations_builder.script_exists("a-script-that-does-not-exist"));
}


TEST_F(TheWeepingHouse_ConfigurationsBuilderWithAllegroRenderingFixtureTest_WITH_ASSEMBLED_configurations_builder,
   entity_exists__will_return_true_if_the_entity_is_present)
{
   // TODO: do not use "assemble_room" for this test
   configurations_builder.assemble_room("my_test_room_name", "This is a test room");
   EXPECT_EQ(true, configurations_builder.entity_exists("my_test_room_name_bg"));
}


TEST_F(TheWeepingHouse_ConfigurationsBuilderWithAllegroRenderingFixtureTest_WITH_ASSEMBLED_configurations_builder,
   entity_exists__will_return_false_if_the_entity_is_not_present)
{
   EXPECT_EQ(false, configurations_builder.entity_exists("an-entity-that-does-not-exist"));
}


TEST_F(TheWeepingHouse_ConfigurationsBuilderWithAllegroRenderingFixtureTest_WITH_ASSEMBLED_configurations_builder,
   assemble_room__will_add_a_room_to_the_configuration_with_the_expected_properties)
{
   AllegroFlare::BitmapBin &bitmap_bin = get_bitmap_bin_ref();
   bitmap_bin.set_full_path(TEST_FIXTURE_BITMAPS_FOLDER);

   configurations_builder.assemble_room("my_test_room_name", "This is a test room");

   // creates a room
   ASSERT_EQ(true, configurations_builder.room_exists("my_test_room_name"));
   EXPECT_NE(nullptr, configurations_builder.get_room_dictionary()["my_test_room_name"]);

   // creates a background
   ASSERT_EQ(true, configurations_builder.entity_exists("my_test_room_name_bg"));
   EXPECT_NE(nullptr, configurations_builder.get_entity_dictionary()["my_test_room_name_bg"]);

   // creates an "observe_..." script for the background
   ASSERT_EQ(true, configurations_builder.script_exists("observe_my_test_room_name"));
   ASSERT_EQ(1, configurations_builder.get_script_dictionary()["observe_my_test_room_name"].get_lines().size());
   EXPECT_EQ(
      "DIALOG: This is a test room",
      configurations_builder.get_script_dictionary()["observe_my_test_room_name"].get_lines()[0]
   );

   // an association exists for the background entity and the room
   EXPECT_EQ(true, configurations_builder.entity_room_association_exists("my_test_room_name_bg", "my_test_room_name"));
}


TEST_F(TheWeepingHouse_ConfigurationsBuilderWithAllegroRenderingFixtureTest_WITH_ASSEMBLED_configurations_builder,
   the_production_configuration_has_the_expected_elements)
{
   AllegroFlare::Prototypes::FixedRoom2D::Configuration configuration = configurations_builder.build();
   EXPECT_EQ(1, configuration.get_entity_dictionary().count("front_porch_door"));

   EXPECT_EQ(true, configurations_builder.entity_room_association_exists("front_porch_door", "front_porch"));
   EXPECT_EQ("front_porch", configuration.get_entity_room_associations()["front_porch_door"]);
}




#include <TheWeepingHouse/Runner.hpp>

TEST(TheWeepingHouse_ConfigurationsBuilder_Test, INTERACTIVE__works_in_the_runner)
{
   TheWeepingHouse::Runner runner;
   //runner.run("test");
   SUCCEED();
}



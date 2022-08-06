

#include <TheWeepingHouse/Configurations/Primary.hpp>
#include <TheWeepingHouse/EntityFactory.hpp>
#include <AllegroFlare/Prototypes/FixedRoom2D/RoomFactory.hpp>
#include <stdexcept>
#include <sstream>


namespace TheWeepingHouse
{
namespace Configurations
{


Primary::Primary()
{
}


Primary::~Primary()
{
}


AllegroFlare::Prototypes::FixedRoom2D::Configuration Primary::build(AllegroFlare::BitmapBin* bitmap_bin, AllegroFlare::FontBin* font_bin, AllegroFlare::EventEmitter* event_emitter, AllegroFlare::Prototypes::FixedRoom2D::EntityCollectionHelper* entity_collection_helper__this_is_a_hack)
{
   if (!(bitmap_bin))
      {
         std::stringstream error_message;
         error_message << "Primary" << "::" << "build" << ": error: " << "guard \"bitmap_bin\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(font_bin))
      {
         std::stringstream error_message;
         error_message << "Primary" << "::" << "build" << ": error: " << "guard \"font_bin\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(event_emitter))
      {
         std::stringstream error_message;
         error_message << "Primary" << "::" << "build" << ": error: " << "guard \"event_emitter\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(entity_collection_helper__this_is_a_hack))
      {
         std::stringstream error_message;
         error_message << "Primary" << "::" << "build" << ": error: " << "guard \"entity_collection_helper__this_is_a_hack\" not met";
         throw std::runtime_error(error_message.str());
      }
   const std::string MAIN_HALLWAY = "main_hallway";
   const std::string FRONT_PATIO = "front_patio";

   const std::string FRONT_PATIO_DOOR = "front_patio_door";

   AllegroFlare::Prototypes::FixedRoom2D::Configuration result;

   AllegroFlare::InventoryIndex &inventory_index = result.get_inventory_index_ref();
   AllegroFlare::Inventory &af_inventory = result.get_af_inventory_ref();
   AllegroFlare::Inventory &flags = result.get_flags_ref();
   std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Entities::Base*> &entity_dictionary =
      result.get_entity_dictionary_ref();
   std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Room*> &room_dictionary =
      result.get_room_dictionary_ref();
   std::map<std::string, std::string> &entity_room_associations =
      result.get_entity_room_associations_ref();
   std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Script> &script_dictionary =
      result.get_script_dictionary_ref();
   std::string &starting_in_room_identifier = result.get_starting_in_room_identifier_ref();


   TheWeepingHouse::EntityFactory entity_factory(bitmap_bin);
   entity_factory.set_hide_hitspots(true);

   AllegroFlare::Prototypes::FixedRoom2D::RoomFactory room_factory(
      bitmap_bin, font_bin, event_emitter, entity_collection_helper__this_is_a_hack
   );

   inventory_index = AllegroFlare::InventoryIndex::build_placeholder_inventory_index();

   af_inventory.add_item(1);
   af_inventory.add_item(4);
   af_inventory.add_item(3);

   room_dictionary = {
      { "front_hall", room_factory.create_room() },
      { "study", room_factory.create_room() },
      { FRONT_PATIO, room_factory.create_room() },
   };

   entity_dictionary = {
      { "front_patio_bg", entity_factory.create_background("room_2.png", "observe_front_patio") },
      { "front_hall_bg", entity_factory.create_background("room_0.png", "observe_front_hall") },
      { "main_hallway_bg", entity_factory.create_background("room_1.png", "observe_main_hallway") },

      { "door1", entity_factory.create_rectangle_hitspot(1725, 440, 60, 350, "Door 1", "observe_door1") },
      { "door2", entity_factory.create_rectangle_hitspot(115, 440, 60, 350, "Door 2", "observe_door2") },
      { FRONT_PATIO_DOOR, entity_factory.create_rectangle_hitspot(1725, 440, 60, 350, "Door 2", "observe_front_patio_door") },
      { "wall_art", entity_factory.create_ellipse_hitspot(1150, 450, 60, 60, "Wall Art", "observe_wall_art") },
   };

   entity_room_associations = {
      { "front_hall_bg", "front_hall" },
      { "main_hallway_bg", "study" },

      { "front_patio_bg", FRONT_PATIO },
      { FRONT_PATIO_DOOR, FRONT_PATIO },

      { "door1", "front_hall" },
      { "door2", "study" },
      //{ "chair", "front_hall" },
      { "table", "front_hall" },
      { "wall_art", "front_hall" },
      { "keys", "front_hall" },
      { "main_hallway_bg", MAIN_HALLWAY },
   };

   script_dictionary = {
      { "observe_front_patio_door", AllegroFlare::Prototypes::FixedRoom2D::Script({
            "DIALOG: Oh wow, it's unlocked.  I'm going inside.",
            "ENTER_ROOM: front_hall",
      })},
      { "observe_front_patio", AllegroFlare::Prototypes::FixedRoom2D::Script({
            "DIALOG: What a nice place... but it doesn't look very invnting.  I'd better see if I can get inside."
      })},
      { "observe_front_hall", AllegroFlare::Prototypes::FixedRoom2D::Script({
            "DIALOG: This is a pretty dark room. | It's kinda hard to see anything, to be honest."
      })},
      { "observe_main_hallway", AllegroFlare::Prototypes::FixedRoom2D::Script({
            "DIALOG: This is a pretty dark room. | It's kinda hard to see anything, to be honest."
      })},
      { "observe_door1", AllegroFlare::Prototypes::FixedRoom2D::Script({
            "DIALOG: Just a regular door. | I'm going to step through it.",
            "ENTER_ROOM: study",
      })},
      { "observe_door2", AllegroFlare::Prototypes::FixedRoom2D::Script({
            "DIALOG: A regular door. | I'll go in.",
            "ENTER_ROOM: front_hall",
      })},
      { "signal_hello", AllegroFlare::Prototypes::FixedRoom2D::Script({
            "SIGNAL: Hello what's going on?"})
      },
      { "collect_keys", AllegroFlare::Prototypes::FixedRoom2D::Script({
            "COLLECT: keys"
      })},
      { "observe_table", AllegroFlare::Prototypes::FixedRoom2D::Script({
            "DIALOG: Hmm. Interesting, there's a key on this table."
      })},
      { "observe_wall_art", AllegroFlare::Prototypes::FixedRoom2D::Script({
            "DIALOG: That's some interesting art on the wall.  I wonder what it's for.",
      })},
   };

   starting_in_room_identifier = FRONT_PATIO;
    
   return result;
}
} // namespace Configurations
} // namespace TheWeepingHouse



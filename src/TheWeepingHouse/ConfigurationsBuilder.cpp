

#include <TheWeepingHouse/ConfigurationsBuilder.hpp>
#include <stdexcept>
#include <sstream>
#include <TheWeepingHouse/EntityFactory.hpp>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>


namespace TheWeepingHouse
{


ConfigurationsBuilder::ConfigurationsBuilder(AllegroFlare::BitmapBin* bitmap_bin, AllegroFlare::FontBin* font_bin, AllegroFlare::EventEmitter* event_emitter, AllegroFlare::Prototypes::FixedRoom2D::EntityCollectionHelper* entity_collection_helper__this_is_a_hack)
   : bitmap_bin(bitmap_bin)
   , font_bin(font_bin)
   , event_emitter(event_emitter)
   , entity_collection_helper__this_is_a_hack(entity_collection_helper__this_is_a_hack)
   , result_configuration()
   , built(false)
   , inventory_index(result_configuration.get_inventory_index_ref())
   , af_inventory(result_configuration.get_af_inventory_ref())
   , flags(result_configuration.get_flags_ref())
   , entity_dictionary(result_configuration.get_entity_dictionary_ref())
   , room_dictionary(result_configuration.get_room_dictionary_ref())
   , entity_room_associations(result_configuration.get_entity_room_associations_ref())
   , script_dictionary(result_configuration.get_script_dictionary_ref())
   , starting_in_room_identifier(result_configuration.get_starting_in_room_identifier_ref())
   , room_factory(bitmap_bin, font_bin, event_emitter, entity_collection_helper__this_is_a_hack)
{
}


ConfigurationsBuilder::~ConfigurationsBuilder()
{
}


AllegroFlare::Prototypes::FixedRoom2D::Configuration ConfigurationsBuilder::get_result_configuration()
{
   if (!(built))
      {
         std::stringstream error_message;
         error_message << "ConfigurationsBuilder" << "::" << "get_result_configuration" << ": error: " << "guard \"built\" not met";
         throw std::runtime_error(error_message.str());
      }
   return result_configuration;
}

AllegroFlare::Prototypes::FixedRoom2D::Configuration ConfigurationsBuilder::build()
{
   if (!(bitmap_bin))
      {
         std::stringstream error_message;
         error_message << "ConfigurationsBuilder" << "::" << "build" << ": error: " << "guard \"bitmap_bin\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(font_bin))
      {
         std::stringstream error_message;
         error_message << "ConfigurationsBuilder" << "::" << "build" << ": error: " << "guard \"font_bin\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(event_emitter))
      {
         std::stringstream error_message;
         error_message << "ConfigurationsBuilder" << "::" << "build" << ": error: " << "guard \"event_emitter\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(entity_collection_helper__this_is_a_hack))
      {
         std::stringstream error_message;
         error_message << "ConfigurationsBuilder" << "::" << "build" << ": error: " << "guard \"entity_collection_helper__this_is_a_hack\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (built) return result_configuration;
   built = true;



   const std::string FRONT_PATIO = "front_patio";
   const std::string FRONT_HALLWAY = "front_hallway";
   const std::string MAIN_HALLWAY = "main_hallway";
   const std::string FIRST_FLOOR_STORAGE_ROOM = "first_floor_storage_room";
   const std::string BACK_PORCH = "back_porch";

   const std::string FRONT_PATIO_DOOR = "front_patio_door";



   TheWeepingHouse::EntityFactory entity_factory(bitmap_bin);
   entity_factory.set_hide_hitspots(true);


   inventory_index = AllegroFlare::InventoryIndex::build_placeholder_inventory_index();

   af_inventory.add_item(1);
   af_inventory.add_item(4);
   af_inventory.add_item(3);

   room_dictionary = {
      { FRONT_PATIO, room_factory.create_room() },
      { FRONT_HALLWAY, room_factory.create_room() },
      { MAIN_HALLWAY, room_factory.create_room() },
      { FIRST_FLOOR_STORAGE_ROOM, room_factory.create_room() },
      { BACK_PORCH, room_factory.create_room() },
   };

   entity_dictionary = {
      { "front_patio_bg", entity_factory.create_background("room_2.png", "observe_front_patio") },
      { "front_hallway_bg", entity_factory.create_background("room_0.png", "observe_front_hallway") },
      { "main_hallway_bg", entity_factory.create_background("room_1.png", "observe_main_hallway") },
      { "first_floor_storage_room_bg", entity_factory.create_background("room_3.png", "observe_first_floor_storage_room") },
      { "back_porch_bg", entity_factory.create_background("room_4.png", "observe_back_porch") },

      { "door1", entity_factory.create_rectangle_hitspot(1725, 440, 60, 350, "Door 1", "observe_door1") },
      { "door2", entity_factory.create_rectangle_hitspot(115, 440, 60, 350, "Door 2", "observe_door2") },
      { FRONT_PATIO_DOOR, entity_factory.create_rectangle_hitspot(1725, 440, 60, 350, "Door 2", "observe_front_patio_door") },
      { "wall_art", entity_factory.create_ellipse_hitspot(1150, 450, 60, 60, "Wall Art", "observe_wall_art") },
   };

   entity_room_associations = {
      { "front_patio_bg", FRONT_PATIO },
      { FRONT_PATIO_DOOR, FRONT_PATIO },

      { "front_hallway_bg", FRONT_HALLWAY },
      { "door1", FRONT_HALLWAY },
      { "wall_art", FRONT_HALLWAY },

      { "main_hallway_bg", MAIN_HALLWAY },
      { "door2", MAIN_HALLWAY },

      { "first_floor_storage_room_bg", FIRST_FLOOR_STORAGE_ROOM },

      { "back_porch_bg", BACK_PORCH },
   };


   script_dictionary = {
      { "observe_front_patio", AllegroFlare::Prototypes::FixedRoom2D::Script({
            "DIALOG: What a nice place... but it doesn't look very invnting.  I'd better see if I can get inside."
      })},
      { "observe_front_hallway", AllegroFlare::Prototypes::FixedRoom2D::Script({
            "DIALOG: This is a pretty dark room. | It's kinda hard to see anything, to be honest."
      })},
      { "observe_main_hallway", AllegroFlare::Prototypes::FixedRoom2D::Script({
            "DIALOG: This is a pretty dark room. | It's kinda hard to see anything, to be honest."
      })},
      { "observe_first_floor_storage_room", AllegroFlare::Prototypes::FixedRoom2D::Script({
            "DIALOG: A little storage room.  Looks like some boxes are in here."
      })},
      { "observe_back_porch", AllegroFlare::Prototypes::FixedRoom2D::Script({
            "DIALOG: It sure is nice to have a place out of the rain for now."
      })},


      { "observe_front_patio_door", AllegroFlare::Prototypes::FixedRoom2D::Script({
            "DIALOG: Oh wow, it's unlocked.  I'm going inside.",
            "ENTER_ROOM: " + FRONT_HALLWAY,
      })},
      { "observe_door1", AllegroFlare::Prototypes::FixedRoom2D::Script({
            "DIALOG: Just a regular door. | I'm going to step through it.",
            "ENTER_ROOM: " + MAIN_HALLWAY,
      })},
      { "observe_door2", AllegroFlare::Prototypes::FixedRoom2D::Script({
            "DIALOG: A regular door. | I'll go in.",
            "ENTER_ROOM: " + FRONT_HALLWAY,
      })},
      { "collect_keys", AllegroFlare::Prototypes::FixedRoom2D::Script({
            "COLLECT: keys"
      })},
      { "observe_wall_art", AllegroFlare::Prototypes::FixedRoom2D::Script({
            "DIALOG: That's some interesting art on the wall.  I wonder what it's for.",
      })},
   };

   //const std::string FRONT_PATIO = "front_patio";
   //const std::string FRONT_HALLWAY = "front_hall";
   //const std::string MAIN_HALLWAY = "main_hallway";
   //const std::string FIRST_FLOOR_STORAGE_ROOM = "first_floor_storage_room";
   //const std::string BACK_PORCH = "back_porch";
   starting_in_room_identifier = FRONT_PATIO;
    
   built = true;

   return result_configuration;
}

bool ConfigurationsBuilder::assemble_room(std::string name, std::string background_bitmap_identifier, std::string observe_script_text)
{
   if (!((!room_exists(name))))
      {
         std::stringstream error_message;
         error_message << "ConfigurationsBuilder" << "::" << "assemble_room" << ": error: " << "guard \"(!room_exists(name))\" not met";
         throw std::runtime_error(error_message.str());
      }
   //room_dictionary[name] = room_factory.create_room();
   return true;
}

bool ConfigurationsBuilder::room_exists(std::string name)
{
   return (room_dictionary.count(name) > 0);
}

void ConfigurationsBuilder::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   if (!((!built)))
      {
         std::stringstream error_message;
         error_message << "ConfigurationsBuilder" << "::" << "set_font_bin" << ": error: " << "guard \"(!built)\" not met";
         throw std::runtime_error(error_message.str());
      }
   room_factory.set_font_bin(font_bin);
   this->font_bin = font_bin;
   return;
}

void ConfigurationsBuilder::set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin)
{
   if (!((!built)))
      {
         std::stringstream error_message;
         error_message << "ConfigurationsBuilder" << "::" << "set_bitmap_bin" << ": error: " << "guard \"(!built)\" not met";
         throw std::runtime_error(error_message.str());
      }
   room_factory.set_bitmap_bin(bitmap_bin);
   this->bitmap_bin = bitmap_bin;
   return;
}

void ConfigurationsBuilder::set_event_emitter(AllegroFlare::EventEmitter* event_emitter)
{
   if (!((!built)))
      {
         std::stringstream error_message;
         error_message << "ConfigurationsBuilder" << "::" << "set_event_emitter" << ": error: " << "guard \"(!built)\" not met";
         throw std::runtime_error(error_message.str());
      }
   room_factory.set_event_emitter(event_emitter);
   this->event_emitter = event_emitter;
   return;
}

void ConfigurationsBuilder::set_entity_collection_helper__this_is_a_hack(AllegroFlare::Prototypes::FixedRoom2D::EntityCollectionHelper* entity_collection_helper__this_is_a_hack)
{
   if (!((!built)))
      {
         std::stringstream error_message;
         error_message << "ConfigurationsBuilder" << "::" << "set_entity_collection_helper__this_is_a_hack" << ": error: " << "guard \"(!built)\" not met";
         throw std::runtime_error(error_message.str());
      }
   room_factory.set_entity_collection_helper(entity_collection_helper__this_is_a_hack);
   this->entity_collection_helper__this_is_a_hack = entity_collection_helper__this_is_a_hack;
   return;
}
} // namespace TheWeepingHouse



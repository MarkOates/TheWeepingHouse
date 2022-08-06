

#include <TheWeepingHouse/ConfigurationsBuilder.hpp>
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
   , entity_factory(bitmap_bin)
{
}


ConfigurationsBuilder::~ConfigurationsBuilder()
{
}


std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Entities::Base*>& ConfigurationsBuilder::get_entity_dictionary()
{
   return entity_dictionary;
}


std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Room*>& ConfigurationsBuilder::get_room_dictionary()
{
   return room_dictionary;
}


std::map<std::string, std::string>& ConfigurationsBuilder::get_entity_room_associations()
{
   return entity_room_associations;
}


std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Script>& ConfigurationsBuilder::get_script_dictionary()
{
   return script_dictionary;
}


void ConfigurationsBuilder::you_build()
{
   // rooms
   const std::string FRONT_PORCH = "front_porch";
   const std::string FRONT_HALLWAY = "front_hallway";
   const std::string MAIN_HALLWAY = "main_hallway";
   const std::string FIRST_FLOOR_STORAGE_ROOM = "first_floor_storage_room";
   const std::string BACK_PORCH = "back_porch";

   // entities
   const std::string FRONT_PORCH_DOOR = "front_porch_door";


   // configs
   starting_in_room_identifier = FRONT_HALLWAY;
   entity_factory.set_hide_hitspots(false);


   // build the inventory
   inventory_index = AllegroFlare::InventoryIndex::build_placeholder_inventory_index();
   af_inventory.add_item(1);
   af_inventory.add_item(4);
   af_inventory.add_item(3);


   // fill the entity dictionary
   entity_dictionary = {
      { "door1", entity_factory.create_rectangle_hitspot(1725, 440, 60, 350, "Door 1", "observe_door1") },
      { "door2", entity_factory.create_rectangle_hitspot(115, 440, 60, 350, "Door 2", "observe_door2") },
      { FRONT_PORCH_DOOR, entity_factory.create_rectangle_hitspot(1725, 440, 60, 350, "Door 2", "observe_front_porch_door") },
      { "wall_art", entity_factory.create_ellipse_hitspot(1150, 450, 60, 60, "Wall Art", "observe_wall_art") },
   };


   // add the associations
   entity_room_associations = {
      { FRONT_PORCH_DOOR, FRONT_PORCH },

      { "door1", FRONT_HALLWAY },
      { "wall_art", FRONT_HALLWAY },

      { "door2", MAIN_HALLWAY },
   };


   // add the scripts
   script_dictionary = {
      { "observe_front_porch_door", AllegroFlare::Prototypes::FixedRoom2D::Script({
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


   assemble_room(FRONT_PORCH, "What a nice place... but it doesn't look very invnting.  "
                              "I'd better see if I can get inside.");
   assemble_room(FRONT_HALLWAY, "This is a pretty dark room. | I'd better see if I can get inside.");
   assemble_room(MAIN_HALLWAY, "This is a pretty dark room. | It's kinda hard to see anything, to be honest.");
   assemble_room(FIRST_FLOOR_STORAGE_ROOM, "Looks like a little room for storage.  There are some boxes here.");
   assemble_room(BACK_PORCH, "It sure is nice to have a place out of hte rain for now.");



   return;
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

void ConfigurationsBuilder::set_start_room(std::string room_name)
{
   starting_in_room_identifier = room_name;
   return;
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
   you_build();
   built = true;
   return result_configuration;
}

bool ConfigurationsBuilder::assemble_room(std::string room_name, std::string observe_script_text)
{
   if (!((!room_exists(room_name))))
      {
         std::stringstream error_message;
         error_message << "ConfigurationsBuilder" << "::" << "assemble_room" << ": error: " << "guard \"(!room_exists(room_name))\" not met";
         throw std::runtime_error(error_message.str());
      }
   std::string generated_script_name = "observe_" + room_name;
   std::string generated_background_entity_name = room_name + "_bg";
   std::string expected_background_bitmap_name = "room_" + room_name + ".png";

   // create the room
   room_dictionary[room_name] = room_factory.create_room();

   // create the background entity
   // TODO: check if it exists first
   entity_dictionary[generated_background_entity_name] = 
      entity_factory.create_background(expected_background_bitmap_name, generated_script_name);

   // add the association for the background entity and the room
   // TODO: check if an association already exists for this entity
   entity_room_associations[generated_background_entity_name] = room_name;

   // create the "observe" script for the background entity
   // TODO: check if the script already exists
   // TODO: validate that the observe_script_text contains no newlines
   script_dictionary[generated_script_name] =
      AllegroFlare::Prototypes::FixedRoom2D::Script({ "DIALOG: " + observe_script_text });

   return true;
}

void ConfigurationsBuilder::add_script(std::string script_name, std::vector<std::string> script_lines)
{
   if (!((!script_exists(script_name))))
      {
         std::stringstream error_message;
         error_message << "ConfigurationsBuilder" << "::" << "add_script" << ": error: " << "guard \"(!script_exists(script_name))\" not met";
         throw std::runtime_error(error_message.str());
      }
   script_dictionary[script_name] = AllegroFlare::Prototypes::FixedRoom2D::Script(script_lines);
   return;
}

bool ConfigurationsBuilder::room_exists(std::string room_name)
{
   return (room_dictionary.count(room_name) > 0);
}

bool ConfigurationsBuilder::script_exists(std::string script_name)
{
   return (script_dictionary.count(script_name) > 0);
}

bool ConfigurationsBuilder::entity_exists(std::string entity_name)
{
   return (entity_dictionary.count(entity_name) > 0);
}

bool ConfigurationsBuilder::entity_room_association_exists(std::string entity_name, std::string room_name)
{
   return (entity_room_associations.count(entity_name) > 0) && entity_room_associations[entity_name] == room_name;
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
   entity_factory.set_bitmap_bin(bitmap_bin);
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





#include <TheWeepingHouse/ConfigurationsBuilder.hpp>

#include <TheWeepingHouse/ConfigurationTMJLoader.hpp>
#include <TheWeepingHouse/FileExistenceChecker.hpp>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>


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


std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Entities::Base*>& ConfigurationsBuilder::get_entity_dictionary() const
{
   return entity_dictionary;
}


std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Room*>& ConfigurationsBuilder::get_room_dictionary() const
{
   return room_dictionary;
}


std::map<std::string, std::string>& ConfigurationsBuilder::get_entity_room_associations() const
{
   return entity_room_associations;
}


std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Script>& ConfigurationsBuilder::get_script_dictionary() const
{
   return script_dictionary;
}


std::string ConfigurationsBuilder::get_room_name(float x, float y)
{
   int room_x = (int)(x / 1920.0);
   int room_y = (int)(y / 1080.0);

   if (room_x == 0 && room_y == 2) return "UNDEF";
   if (room_x == 1 && room_y == 2) return "front_porch";
   if (room_x == 2 && room_y == 2) return "front_hallway";
   if (room_x == 3 && room_y == 2) return "main_hallway";
   if (room_x == 4 && room_y == 2) return "first_floor_storage_room";
   if (room_x == 5 && room_y == 2) return "back_porch";
   if (room_x == 6 && room_y == 2) return "back_porch_detail";

   if (room_x == 0 && room_y == 1) return "UNDEF";
   if (room_x == 1 && room_y == 1) return "upstairs_utility_room";
   if (room_x == 2 && room_y == 1) return "upstairs_stairwell";
   if (room_x == 3 && room_y == 1) return "upstairs_living_hallway";
   if (room_x == 4 && room_y == 1) return "master_entry";
   if (room_x == 5 && room_y == 1) return "UNDEF";
   if (room_x == 6 && room_y == 1) return "basement";

   if (room_x == 0 && room_y == 0) return "UNDEF";
   if (room_x == 1 && room_y == 0) return "attic";
   if (room_x == 2 && room_y == 0) return "girls_room";
   if (room_x == 3 && room_y == 0) return "boys_room";
   if (room_x == 4 && room_y == 0) return "master_bedroom";
   if (room_x == 5 && room_y == 0) return "master_balcony";
   if (room_x == 6 && room_y == 0) return "UNDER";


   // 'upstairs_utility_room':    
   // 'upstairs_stairwell':      
   // 'upstairs_living_hallway':
   // 'master_entry'
   // 'master_bedroom':           
   // 'master_balcony':          

   // 'attic'
   // 'boys_room'
   // 'girls_room'
   // 'back_porch_detail'
   // 'basement'


   return "UNRECOGNIZED_ROOM_NAME at coordiates";
}

void ConfigurationsBuilder::build_from_tmj_source(std::string filename)
{
   TheWeepingHouse::ConfigurationTMJLoader loader(filename);
   loader.load();

   //std::string current_room = get_room_name"front_hallway";
   for (auto &object : loader.get_objects())
   {
      if (object.get_name().empty())
      {
         std::cout << "[TheWeepingHouse::ConfigurationsBuilder::build_from_tmj_source]: INFO: "
                   << "found an entity with no name, skipping."
                   << std::endl;
         continue;
      }
      //if (object.is_type("")) // an empty type, assume a hitspot
      //{
         std::string inferred_room_name = get_room_name(object.get_x(), object.get_y());
         int object_x = (int)(object.get_x()) % 1920;
         int object_y = (int)(object.get_y()) % 1080;
         std::string object_name = object.get_name();
         std::string script = object.get_script();
         if (script.empty()) script = "DIALOG: hmm... nothing.";

         std::vector<std::string> script_lines = split(script, '\n');

         std::string script_name = inferred_room_name + "/observe_" + object_name;

         add_hitspot_to_room(
            inferred_room_name,
            object_name,
            object_x,
            object_y,
            object.get_w(),
            object.get_h(),
            "NO-LABEL",
            script_name //"" // object.get_script_name_to_play()
         );

         add_script(script_name, script_lines);
      //}
   }
}

void ConfigurationsBuilder::you_build()
{
   entity_factory.set_hide_hitspots(true);
   starting_in_room_identifier = "front_porch";
   //starting_in_room_identifier = "upstairs_utility_room";

   // rooms
   const std::string FRONT_PORCH = "front_porch";
   const std::string FRONT_HALLWAY = "front_hallway";
   const std::string MAIN_HALLWAY = "main_hallway";
   const std::string FIRST_FLOOR_STORAGE_ROOM = "first_floor_storage_room";
   const std::string BACK_PORCH = "back_porch";
   const std::string BACK_PORCH_DETAIL = "back_porch_detail";
   const std::string BASEMENT = "basement";
   const std::string BOYS_ROOM = "boys_room";
   const std::string GIRLS_ROOM = "girls_room";
   const std::string ATTIC = "attic";


   // main floor
   assemble_room(FRONT_HALLWAY, "Hello?  Is anybody home?");
   assemble_room(FRONT_PORCH, "What a nice place... but it doesn't look very inviting.  "
                              "I'd better see if I can get inside.");
   assemble_room(MAIN_HALLWAY, "This is a pretty dark room. | It's kinda hard to see anything, to be honest.");
   assemble_room(FIRST_FLOOR_STORAGE_ROOM, "Looks like a little room for storage.  There are some boxes here.");
   assemble_room(BACK_PORCH, "It sure is nice to have a place out of the rain for now.");
   assemble_room(BACK_PORCH_DETAIL, "It sure is nice to have a place out of the rain for now.");


   // upstairs floor
   assemble_room("upstairs_stairwell", "There seems to be a lot of space here.");
   assemble_room("upstairs_utility_room", "A utility room. There's a lot of junk in here.");
   assemble_room("upstairs_living_hallway", "It sure is quiet. | It doesn't even look like there's anybody "
                                            "living here.");
   assemble_room("master_entry", "Woah. That's a big door.");
   //assemble_room("master_entryway", "Woah. That's a big door.");


   // "3rd" floor
   assemble_room("master_bedroom", "This is a very large room.");
   assemble_room("master_balcony", "It's still so dark out.");
   assemble_room(BOYS_ROOM, "There's hardly anything in this room. | It feels a bit lonely.");
   assemble_room(GIRLS_ROOM, "This looks like a kid's room.");
   assemble_room(ATTIC, "I hope there's no spiders up here.");



   // "-1" floor
   assemble_room(BASEMENT, "Ugh. What a dark and drab place. I'm not sure I want to be here.");




   std::string tmj_path = "data/configurations/production-configuration-03.tmj";
   if (!TheWeepingHouse::FileExistenceChecker(tmj_path).exists())
   {
      // assume this is a local dev or test version (not running from main), so prefix as a hard-coded path
      tmj_path = "/Users/markoates/Repos/TheWeepingHouse/bin/programs/" + tmj_path;
   }

   build_from_tmj_source(tmj_path);

   entity_factory.set_hide_hitspots(true);

   return;
}

void ConfigurationsBuilder::__you_build()
{
   // rooms
   const std::string FRONT_PORCH = "front_porch";
   const std::string FRONT_HALLWAY = "front_hallway";
   const std::string MAIN_HALLWAY = "main_hallway";
   const std::string FIRST_FLOOR_STORAGE_ROOM = "first_floor_storage_room";
   const std::string BACK_PORCH = "back_porch";

   // entities
   const std::string FRONT_PORCH_DOOR = "front_porch_door";
   const std::string BACK_PORCH_DOOR = "back_porch_door";
   const std::string DOOR1 = "door1";
   const std::string DOOR2 = "door2";
   const std::string WALL_ART = "wall_art";


   // configs
   starting_in_room_identifier = FRONT_HALLWAY;
   entity_factory.set_hide_hitspots(false);


   // build the inventory
   inventory_index = AllegroFlare::InventoryIndex::build_placeholder_inventory_index();
   af_inventory.add_item(1);
   af_inventory.add_item(4);
   af_inventory.add_item(3);



   // FRONT PORCH

   assemble_room(FRONT_PORCH, "What a nice place... but it doesn't look very invnting.  "
                              "I'd better see if I can get inside.");

   add_hitspot_to_room(FRONT_PORCH,
      FRONT_PORCH_DOOR, 1600, 460, 90, 270, "Front porch door", "observe_front_porch_door");

   add_script("observe_front_porch_door", {
      "DIALOG: Oh wow, it's unlocked.  I'm going inside.",
      "PLAY_MUSIC_TRACK: rain_on_roof", // <-- WORKS
      //"PLAY_MUSIC_TRACK: heavy_outdoor_rain", // <-- WORKS
      "ENTER_ROOM: " + FRONT_HALLWAY,
   });



   // FRONT HALLWAY

   assemble_room(FRONT_HALLWAY, "This is a pretty dark room. | I'd better see if I can get inside.");

   add_hitspot_to_room(FRONT_HALLWAY,
      DOOR1, 1725, 440, 60, 350, "Door 1", "observe_door1");
   add_ellipse_hitspot_to_room(FRONT_HALLWAY,
      WALL_ART, 1150, 450, 60, 60, "Wall Art", "observe_wall_art");

   add_script("observe_door1", {
      "DIALOG: Just a regular door. | I'm going to step through it.",
      "ENTER_ROOM: " + MAIN_HALLWAY,
   });
   add_script("observe_wall_art", {
      //"PLAY_MUSIC_TRACK: heavy_outdoor_rain", // <-- WORKS
      "DIALOG: That's some interesting art on the wall.  I wonder what it's for.",
   });



   // MAIN HALLWAY

   assemble_room(MAIN_HALLWAY, "This is a pretty dark room. | It's kinda hard to see anything, to be honest.");

   add_hitspot_to_room(MAIN_HALLWAY,
      DOOR2, 115, 440, 60, 350, "Door 2", "observe_door2");

   add_script("observe_door2", {
       "DIALOG: A regular door. | I'll go in.",
      "ENTER_ROOM: " + FRONT_HALLWAY,
   });



   // FIRST FLOOR STORAGE ROOM

   assemble_room(FIRST_FLOOR_STORAGE_ROOM, "Looks like a little room for storage.  There are some boxes here.");

   // Does nothing for now
   //add_script("collect_keys", {
     //"COLLECT: keys"
   //});


   // BACK PORCH

   assemble_room(BACK_PORCH, "It sure is nice to have a place out of the rain for now.");

   add_hitspot_to_room(BACK_PORCH,
      BACK_PORCH_DOOR, 230, 450, 80, 290, "Back porch door", "observe_back_porch_door");

   add_script("observe_back_porch_door", {
      "DIALOG: A regular door. | I'll go in.",
      "ENTER_ROOM: " + FIRST_FLOOR_STORAGE_ROOM,
   });



   starting_in_room_identifier = FRONT_PORCH;


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

bool ConfigurationsBuilder::add_hitspot_to_room(std::string room_name, std::string hitspot_name, float x, float y, float w, float h, std::string label, std::string interact_script_name)
{
   if (!((!entity_exists(hitspot_name))))
   {
      std::stringstream error_message;
      error_message << "ConfigurationsBuilder" << "::" << "add_hitspot_to_room" << ": error: " << "guard \"(!entity_exists(hitspot_name))\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (!((!entity_room_association_exists(hitspot_name, room_name))))
   {
      std::stringstream error_message;
      error_message << "ConfigurationsBuilder" << "::" << "add_hitspot_to_room" << ": error: " << "guard \"(!entity_room_association_exists(hitspot_name, room_name))\" not met";
      throw std::runtime_error(error_message.str());
   }
   hitspot_name = room_name + "/" + hitspot_name;
   entity_dictionary[hitspot_name] =
      entity_factory.create_rectangle_hitspot(x, y, w, h, label, interact_script_name);
   entity_room_associations[hitspot_name] = room_name;
   return true;
}

bool ConfigurationsBuilder::add_ellipse_hitspot_to_room(std::string room_name, std::string hitspot_name, float x, float y, float w, float h, std::string label, std::string interact_script_name)
{
   if (!((!entity_exists(hitspot_name))))
   {
      std::stringstream error_message;
      error_message << "ConfigurationsBuilder" << "::" << "add_ellipse_hitspot_to_room" << ": error: " << "guard \"(!entity_exists(hitspot_name))\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (!((!entity_room_association_exists(hitspot_name, room_name))))
   {
      std::stringstream error_message;
      error_message << "ConfigurationsBuilder" << "::" << "add_ellipse_hitspot_to_room" << ": error: " << "guard \"(!entity_room_association_exists(hitspot_name, room_name))\" not met";
      throw std::runtime_error(error_message.str());
   }
   hitspot_name = room_name + "/" + hitspot_name;
   entity_dictionary[hitspot_name] =
      entity_factory.create_ellipse_hitspot(x, y, w, h, label, interact_script_name);
   entity_room_associations[hitspot_name] = room_name;
   return true;
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
   std::string generated_background_entity_name = room_name + "/background";
   std::string expected_background_bitmap_name = "rooms/room_" + room_name + ".png";

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
   if (script_exists(script_name))
   {
      std::stringstream error_message;
      error_message << "[TheWeepingHouse::ConfigurationsBuilder::add_script]: ERROR: "
                    << "A script with the name \"" << script_name << "\" already exists."
                    << std::endl;
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

std::vector<std::string> ConfigurationsBuilder::split(std::string text, char delimiter)
{
   std::vector<std::string> elems;
   auto result = std::back_inserter(elems);
   std::stringstream ss(text);
   std::string item;
   while (std::getline(ss, item, delimiter)) { *(result++) = item; }
   return elems;
}


} // namespace TheWeepingHouse



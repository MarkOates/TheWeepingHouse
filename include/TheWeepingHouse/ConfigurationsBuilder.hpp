#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/EventEmitter.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/Inventory.hpp>
#include <AllegroFlare/InventoryIndex.hpp>
#include <AllegroFlare/Prototypes/FixedRoom2D/Configuration.hpp>
#include <AllegroFlare/Prototypes/FixedRoom2D/Entities/Base.hpp>
#include <AllegroFlare/Prototypes/FixedRoom2D/EntityCollectionHelper.hpp>
#include <AllegroFlare/Prototypes/FixedRoom2D/Room.hpp>
#include <AllegroFlare/Prototypes/FixedRoom2D/RoomFactory.hpp>
#include <AllegroFlare/Prototypes/FixedRoom2D/Script.hpp>
#include <TheWeepingHouse/EntityFactory.hpp>
#include <map>
#include <string>
#include <vector>


namespace TheWeepingHouse
{
   class ConfigurationsBuilder
   {
   private:
      AllegroFlare::BitmapBin* bitmap_bin;
      AllegroFlare::FontBin* font_bin;
      AllegroFlare::EventEmitter* event_emitter;
      AllegroFlare::Prototypes::FixedRoom2D::EntityCollectionHelper* entity_collection_helper__this_is_a_hack;
      AllegroFlare::Prototypes::FixedRoom2D::Configuration result_configuration;
      bool built;
      AllegroFlare::InventoryIndex& inventory_index;
      AllegroFlare::Inventory& af_inventory;
      AllegroFlare::Inventory& flags;
      std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Entities::Base*>& entity_dictionary;
      std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Room*>& room_dictionary;
      std::map<std::string, std::string>& entity_room_associations;
      std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Script>& script_dictionary;
      std::string& starting_in_room_identifier;
      AllegroFlare::Prototypes::FixedRoom2D::RoomFactory room_factory;
      TheWeepingHouse::EntityFactory entity_factory;

   public:
      ConfigurationsBuilder(AllegroFlare::BitmapBin* bitmap_bin=nullptr, AllegroFlare::FontBin* font_bin=nullptr, AllegroFlare::EventEmitter* event_emitter=nullptr, AllegroFlare::Prototypes::FixedRoom2D::EntityCollectionHelper* entity_collection_helper__this_is_a_hack=nullptr);
      ~ConfigurationsBuilder();

      std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Entities::Base*>& get_entity_dictionary();
      std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Room*>& get_room_dictionary();
      std::map<std::string, std::string>& get_entity_room_associations();
      std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Script>& get_script_dictionary();
      void you_build();
      AllegroFlare::Prototypes::FixedRoom2D::Configuration get_result_configuration();
      void set_start_room(std::string room_name="[unset-room_name]");
      AllegroFlare::Prototypes::FixedRoom2D::Configuration build();
      bool add_hitspot_to_room(std::string room_name="[unset-room_name]", std::string hitspot_name="[unset-hitspot_name]", float x=1920/2, float y=1080/2, float w=100, float h=100, std::string label="[unset-label]", std::string interact_script_name="[unset-interact_script_name]");
      bool add_ellipse_hitspot_to_room(std::string room_name="[unset-room_name]", std::string hitspot_name="[unset-hitspot_name]", float x=1920/2, float y=1080/2, float w=100, float h=100, std::string label="[unset-label]", std::string interact_script_name="[unset-interact_script_name]");
      bool assemble_room(std::string room_name="[unset-room_name]", std::string observe_script_text="[unset-background_bitmap_identifier]");
      void add_script(std::string script_name="[unset-script_name]", std::vector<std::string> script_lines={"[unset-script_lines]"});
      bool room_exists(std::string room_name="[unset-room_name]");
      bool script_exists(std::string script_name="[unset-script_name]");
      bool entity_exists(std::string entity_name="[unset-entity_name]");
      bool entity_room_association_exists(std::string entity_name="[unset-entity_name]", std::string room_name="[unset-entity_name]");
      void set_font_bin(AllegroFlare::FontBin* font_bin=nullptr);
      void set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin=nullptr);
      void set_event_emitter(AllegroFlare::EventEmitter* event_emitter=nullptr);
      void set_entity_collection_helper__this_is_a_hack(AllegroFlare::Prototypes::FixedRoom2D::EntityCollectionHelper* entity_collection_helper__this_is_a_hack=nullptr);
   };
}




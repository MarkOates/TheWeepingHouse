#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/EventEmitter.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/Prototypes/FixedRoom2D/Configuration.hpp>
#include <AllegroFlare/Prototypes/FixedRoom2D/EntityCollectionHelper.hpp>
#include <string>


namespace TheWeepingHouse
{
   class ConfigurationsBuilder
   {
   private:
      AllegroFlare::BitmapBin* bitmap_bin;
      AllegroFlare::FontBin* font_bin;
      AllegroFlare::EventEmitter* event_emitter;
      AllegroFlare::Prototypes::FixedRoom2D::EntityCollectionHelper* entity_collection_helper__this_is_a_hack;
      AllegroFlare::Prototypes::FixedRoom2D::Configuration configuration;
      bool built;

   public:
      ConfigurationsBuilder(AllegroFlare::BitmapBin* bitmap_bin=nullptr, AllegroFlare::FontBin* font_bin=nullptr, AllegroFlare::EventEmitter* event_emitter=nullptr, AllegroFlare::Prototypes::FixedRoom2D::EntityCollectionHelper* entity_collection_helper__this_is_a_hack=nullptr);
      ~ConfigurationsBuilder();

      AllegroFlare::Prototypes::FixedRoom2D::Configuration get_configuration();
      AllegroFlare::Prototypes::FixedRoom2D::Configuration build();
      bool assemble_room(std::string name="[unset-name]", std::string background_bitmap_identifier="[unset-background_bitmap_identifier]", std::string observe_script_text="[unset-background_bitmap_identifier]");
      void set_font_bin(AllegroFlare::FontBin* font_bin=nullptr);
      void set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin=nullptr);
      void set_event_emitter(AllegroFlare::EventEmitter* event_emitter=nullptr);
      void set_entity_collection_helper__this_is_a_hack(AllegroFlare::Prototypes::FixedRoom2D::EntityCollectionHelper* entity_collection_helper__this_is_a_hack=nullptr);
   };
}




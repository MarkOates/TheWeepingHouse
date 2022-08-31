#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/EventEmitter.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/Prototypes/FixedRoom2D/Configuration.hpp>
#include <AllegroFlare/Prototypes/FixedRoom2D/EntityCollectionHelper.hpp>
#include <string>


namespace TheWeepingHouse
{
   namespace Configurations
   {
      class Initial
      {
      private:

      protected:


      public:
         Initial();
         ~Initial();

         static AllegroFlare::Prototypes::FixedRoom2D::Configuration build(AllegroFlare::BitmapBin* bitmap_bin=nullptr, AllegroFlare::FontBin* font_bin=nullptr, AllegroFlare::EventEmitter* event_emitter=nullptr, AllegroFlare::Prototypes::FixedRoom2D::EntityCollectionHelper* entity_collection_helper__this_is_a_hack=nullptr);
         bool assemble_room(std::string name="[unset-name]", std::string background_bitmap_identifier="[unset-background_bitmap_identifier]", std::string observe_script_text="[unset-background_bitmap_identifier]");
      };
   }
}




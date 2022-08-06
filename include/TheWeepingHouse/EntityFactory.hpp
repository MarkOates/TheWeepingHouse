#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/Prototypes/FixedRoom2D/Entities/Base.hpp>
#include <string>


namespace TheWeepingHouse
{
   class EntityFactory
   {
   private:
      AllegroFlare::BitmapBin* bitmap_bin;
      std::string hitspot_rectangle_bitmap_identifier;
      std::string hitspot_circle_bitmap_identifier;
      bool hide_hitspots;

   public:
      EntityFactory(AllegroFlare::BitmapBin* bitmap_bin=nullptr);
      ~EntityFactory();

      void set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin);
      void set_hide_hitspots(bool hide_hitspots);
      bool get_hide_hitspots();
      AllegroFlare::Prototypes::FixedRoom2D::Entities::Base* create_background(std::string bitmap_image_identifier="[unset-bitmap_identifier]", std::string on_interact_script_name="[unset-on_interact_script_name]");
      AllegroFlare::Prototypes::FixedRoom2D::Entities::Base* create_rectangle_hitspot(float x=1920/2, float y=1080/2, float w=100, float h=100, std::string name="[unset-name]", std::string on_interact_script_name="[unset-on_interact_script_name]");
      AllegroFlare::Prototypes::FixedRoom2D::Entities::Base* create_ellipse_hitspot(float center_x=1920/2, float center_y=1080/2, float w=100, float h=100, std::string name="[unset-name]", std::string on_interact_script_name="[unset-on_interact_script_name]");
      AllegroFlare::Prototypes::FixedRoom2D::Entities::Base* create_entity(std::string bitmap_image_identifier="[unset-bitmap_identifier]", float x=1920/2, float y=1080/2, float scale=1.0f, std::string name="[unset-name]", std::string on_interact_script_name="[unset-on_interact_script_name]", float align_x=0.5f, float align_y=1.0f, bool hidden=false);
   };
}




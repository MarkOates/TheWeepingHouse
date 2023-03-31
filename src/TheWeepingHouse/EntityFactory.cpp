

#include <TheWeepingHouse/EntityFactory.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


namespace TheWeepingHouse
{


EntityFactory::EntityFactory(AllegroFlare::BitmapBin* bitmap_bin)
   : bitmap_bin(bitmap_bin)
   , hitspot_rectangle_bitmap_identifier("hitspot_rectangle_1x1.png")
   , hitspot_circle_bitmap_identifier("hitspot_circle_100x100.png")
   , hide_hitspots(false)
{
}


EntityFactory::~EntityFactory()
{
}


void EntityFactory::set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin)
{
   this->bitmap_bin = bitmap_bin;
}


void EntityFactory::set_hide_hitspots(bool hide_hitspots)
{
   this->hide_hitspots = hide_hitspots;
}


bool EntityFactory::get_hide_hitspots() const
{
   return hide_hitspots;
}


AllegroFlare::Prototypes::FixedRoom2D::Entities::Base* EntityFactory::create_background(std::string bitmap_image_identifier, std::string on_interact_script_name)
{
   if (!(bitmap_bin))
   {
      std::stringstream error_message;
      error_message << "[EntityFactory::create_background]: error: guard \"bitmap_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("EntityFactory::create_background: error: guard \"bitmap_bin\" not met");
   }
   AllegroFlare::Prototypes::FixedRoom2D::Entities::Base* result = create_entity(
      bitmap_image_identifier, 0, 0, 1.0, "background", on_interact_script_name, 0, 0
   );
   result->set_cursor_insights_are_hidden(true);
   return result;
}

AllegroFlare::Prototypes::FixedRoom2D::Entities::Base* EntityFactory::create_rectangle_hitspot(float x, float y, float w, float h, std::string name, std::string on_interact_script_name)
{
   if (!(bitmap_bin))
   {
      std::stringstream error_message;
      error_message << "[EntityFactory::create_rectangle_hitspot]: error: guard \"bitmap_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("EntityFactory::create_rectangle_hitspot: error: guard \"bitmap_bin\" not met");
   }
   ALLEGRO_BITMAP* bitmap = bitmap_bin->auto_get(hitspot_rectangle_bitmap_identifier);

   AllegroFlare::Prototypes::FixedRoom2D::Entities::Base* result = new
      AllegroFlare::Prototypes::FixedRoom2D::Entities::Base(bitmap);

   AllegroFlare::Placement2D &placement = result->get_placement_ref();
   result->set_on_cursor_interact_script_name(on_interact_script_name);
   result->set_hidden(hide_hitspots);

   placement.position = {x, y};
   placement.scale = {w, h};
   placement.align = {0, 0};

   result->set("name", name);
   result->set("is_hitspot", true);

   return result;
}

AllegroFlare::Prototypes::FixedRoom2D::Entities::Base* EntityFactory::create_ellipse_hitspot(float center_x, float center_y, float w, float h, std::string name, std::string on_interact_script_name)
{
   if (!(bitmap_bin))
   {
      std::stringstream error_message;
      error_message << "[EntityFactory::create_ellipse_hitspot]: error: guard \"bitmap_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("EntityFactory::create_ellipse_hitspot: error: guard \"bitmap_bin\" not met");
   }
   ALLEGRO_BITMAP* bitmap = bitmap_bin->auto_get(hitspot_circle_bitmap_identifier);
   int bitmap_natural_width = al_get_bitmap_width(bitmap);
   int bitmap_natural_height = al_get_bitmap_height(bitmap);

   AllegroFlare::Prototypes::FixedRoom2D::Entities::Base* result = new
      AllegroFlare::Prototypes::FixedRoom2D::Entities::Base(bitmap);

   AllegroFlare::Placement2D &placement = result->get_placement_ref();
   result->set_on_cursor_interact_script_name(on_interact_script_name);
   result->set_hidden(hide_hitspots);

   placement.position = {center_x, center_y};
   placement.scale = {bitmap_natural_width / w, bitmap_natural_height / h};
   placement.align = {0.5, 0.5};

   result->set("name", name);
   result->set("is_hitspot", true);

   return result;
}

AllegroFlare::Prototypes::FixedRoom2D::Entities::Base* EntityFactory::create_entity(std::string bitmap_image_identifier, float x, float y, float scale, std::string name, std::string on_interact_script_name, float align_x, float align_y, bool hidden)
{
   if (!(bitmap_bin))
   {
      std::stringstream error_message;
      error_message << "[EntityFactory::create_entity]: error: guard \"bitmap_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("EntityFactory::create_entity: error: guard \"bitmap_bin\" not met");
   }
   ALLEGRO_BITMAP* bitmap = bitmap_bin->auto_get(bitmap_image_identifier);

   AllegroFlare::Prototypes::FixedRoom2D::Entities::Base* result = new
      AllegroFlare::Prototypes::FixedRoom2D::Entities::Base(bitmap);

   AllegroFlare::Placement2D &placement = result->get_placement_ref();
   result->set_on_cursor_interact_script_name(on_interact_script_name);
   result->set_hidden(hidden);

   placement.position = {x, y};
   placement.scale = {scale, scale};
   placement.align = {align_x, align_y};
   if (bitmap) placement.size = {(float)al_get_bitmap_width(bitmap), (float)al_get_bitmap_height(bitmap)};

   result->set("name", name);

   return result;
}


} // namespace TheWeepingHouse



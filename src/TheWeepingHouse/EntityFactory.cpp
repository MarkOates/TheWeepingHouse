

#include <TheWeepingHouse/EntityFactory.hpp>
#include <stdexcept>
#include <sstream>


namespace TheWeepingHouse
{


EntityFactory::EntityFactory(AllegroFlare::BitmapBin* bitmap_bin)
   : bitmap_bin(bitmap_bin)
{
}


EntityFactory::~EntityFactory()
{
}


AllegroFlare::Prototypes::FixedRoom2D::Entities::Base* EntityFactory::create_entity(std::string bitmap_image_identifier, float x, float y, float scale, std::string name, std::string on_interact_script_name, float align_x, float align_y)
{
   if (!(bitmap_bin))
      {
         std::stringstream error_message;
         error_message << "EntityFactory" << "::" << "create_entity" << ": error: " << "guard \"bitmap_bin\" not met";
         throw std::runtime_error(error_message.str());
      }
   ALLEGRO_BITMAP* bitmap = bitmap_bin->auto_get(bitmap_image_identifier);

   AllegroFlare::Prototypes::FixedRoom2D::Entities::Base* result = new
      AllegroFlare::Prototypes::FixedRoom2D::Entities::Base(bitmap);

   AllegroFlare::Placement2D &placement = result->get_placement_ref();
   result->set_on_cursor_interact_script_name(on_interact_script_name);

   placement.position = {x, y};
   placement.scale = {scale, scale};
   placement.align = {align_x, align_y};
   if (bitmap) placement.size = {(float)al_get_bitmap_width(bitmap), (float)al_get_bitmap_height(bitmap)};

   result->set("name", name);

   return result;
}
} // namespace TheWeepingHouse



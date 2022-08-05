#pragma once


#include <AllegroFlare/Shader.hpp>
#include <allegro5/allegro.h>
#include <string>


namespace TheWeepingHouse
{
   namespace Shaders
   {
      class Multiply : public AllegroFlare::Shader
      {
      private:
         bool initialized;

      public:
         Multiply();
         ~Multiply();

         void initialize();
         void activate();
         void set_tint(ALLEGRO_COLOR flat_color={});
         void set_tint_intensity(float tint_intensity=1.0f);
         static std::string obtain_vertex_source();
         static std::string obtain_fragment_source();
      };
   }
}




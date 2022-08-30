

#include <TheWeepingHouse/Shaders/Multiply.hpp>
#include <stdexcept>
#include <sstream>
#include <iostream>


namespace TheWeepingHouse
{
namespace Shaders
{


Multiply::Multiply()
   : AllegroFlare::Shader(obtain_vertex_source(), obtain_fragment_source())
   , initialized(false)
   , tint(ALLEGRO_COLOR{1, 1, 1, 1})
   , tint_intensity(1.0f)
{
}


Multiply::~Multiply()
{
}


void Multiply::set_tint(ALLEGRO_COLOR tint)
{
   this->tint = tint;
}


void Multiply::set_tint_intensity(float tint_intensity)
{
   this->tint_intensity = tint_intensity;
}


ALLEGRO_COLOR Multiply::get_tint() const
{
   return tint;
}


float Multiply::get_tint_intensity() const
{
   return tint_intensity;
}


void Multiply::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "Multiply" << "::" << "initialize" << ": error: " << "guard \"(!initialized)\" not met";
      throw std::runtime_error(error_message.str());
   }
   AllegroFlare::Shader::initialize();
   initialized = true;
   return;
}

void Multiply::activate()
{
   if (!initialized)
   {
      throw std::runtime_error("[TheWeepingHouse::Shaders::Multiply] Attempting to activate() "
                               "shader before it has been initialized");
   }
   AllegroFlare::Shader::activate();
   set_values_to_activated_shader();
   return;
}

void Multiply::set_values_to_activated_shader()
{
   set_vec3("tint", tint.r, tint.g, tint.b);
   set_float("tint_intensity", tint_intensity);
   return;
}

std::string Multiply::obtain_vertex_source()
{
   static const std::string source = R"DELIM(
     attribute vec4 al_pos;
     attribute vec4 al_color;
     attribute vec2 al_texcoord;
     uniform mat4 al_projview_matrix;
     varying vec4 varying_color;
     varying vec2 varying_texcoord;

     void main()
     {
        varying_color = al_color;
        varying_texcoord = al_texcoord;
        gl_Position = al_projview_matrix * al_pos;
     }
   )DELIM";
   return source;
}

std::string Multiply::obtain_fragment_source()
{
   static const std::string source = R"DELIM(
     uniform sampler2D al_tex;
     uniform float tint_intensity;
     uniform vec3 tint;
     varying vec4 varying_color;
     varying vec2 varying_texcoord;

     void main()
     {
        vec4 tmp = texture2D(al_tex, varying_texcoord);
        float inverse_tint_intensity = 1.0 - tint_intensity;
        //tmp.r = (tmp.r * inverse_tint_intensity + tint.r * tint_intensity) * tmp.a;
        //tmp.g = (tmp.g * inverse_tint_intensity + tint.g * tint_intensity) * tmp.a;
        //tmp.b = (tmp.b * inverse_tint_intensity + tint.b * tint_intensity) * tmp.a;
        //tmp.a = tmp.a;
        //gl_FragColor = tmp * tint;
        tmp.r = (tmp.r * (0.4 + 0.6 * tmp.r) * tint.r);
        tmp.g = (tmp.g * (0.4 + 0.6 * tmp.g) * tint.g); //inverse_tint_intensity + tint.g * tint_intensity) * tmp.a;
        tmp.b = (tmp.b * (0.5 + 0.5 * tmp.b) * tint.b); //inverse_tint_intensity + tint.b * tint_intensity) * tmp.a;
        tmp.a = tmp.a;

        gl_FragColor = tmp;
     }
   )DELIM";
   return source;
}
} // namespace Shaders
} // namespace TheWeepingHouse



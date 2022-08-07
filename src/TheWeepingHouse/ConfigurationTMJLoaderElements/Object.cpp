

#include <TheWeepingHouse/ConfigurationTMJLoaderElements/Object.hpp>



namespace TheWeepingHouse
{
namespace ConfigurationTMJLoaderElements
{


Object::Object(std::string name, std::string type, float x, float y, float w, float h, std::string script, std::string script_name_to_play)
   : name(name)
   , type(type)
   , x(x)
   , y(y)
   , w(w)
   , h(h)
   , script(script)
   , script_name_to_play(script_name_to_play)
{
}


Object::~Object()
{
}


void Object::set_name(std::string name)
{
   this->name = name;
}


void Object::set_type(std::string type)
{
   this->type = type;
}


void Object::set_x(float x)
{
   this->x = x;
}


void Object::set_y(float y)
{
   this->y = y;
}


void Object::set_w(float w)
{
   this->w = w;
}


void Object::set_h(float h)
{
   this->h = h;
}


void Object::set_script(std::string script)
{
   this->script = script;
}


void Object::set_script_name_to_play(std::string script_name_to_play)
{
   this->script_name_to_play = script_name_to_play;
}


std::string Object::get_name()
{
   return name;
}


std::string Object::get_type()
{
   return type;
}


float Object::get_x()
{
   return x;
}


float Object::get_y()
{
   return y;
}


float Object::get_w()
{
   return w;
}


float Object::get_h()
{
   return h;
}


std::string Object::get_script()
{
   return script;
}


std::string Object::get_script_name_to_play()
{
   return script_name_to_play;
}


} // namespace ConfigurationTMJLoaderElements
} // namespace TheWeepingHouse



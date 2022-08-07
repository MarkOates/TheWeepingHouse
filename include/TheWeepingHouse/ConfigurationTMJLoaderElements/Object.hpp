#pragma once


#include <string>


namespace TheWeepingHouse
{
   namespace ConfigurationTMJLoaderElements
   {
      class Object
      {
      private:
         std::string name;
         std::string type;
         float x;
         float y;
         float w;
         float h;
         std::string script;
         std::string script_name_to_play;

      public:
         Object(std::string name="[Object::unset-name]", std::string type="[Object::unset-type]", float x=0.0, float y=0.0, float w=0.0, float h=0.0, std::string script="", std::string script_name_to_play="");
         ~Object();

         void set_name(std::string name);
         void set_type(std::string type);
         void set_x(float x);
         void set_y(float y);
         void set_w(float w);
         void set_h(float h);
         void set_script(std::string script);
         void set_script_name_to_play(std::string script_name_to_play);
         std::string get_name();
         std::string get_type();
         float get_x();
         float get_y();
         float get_w();
         float get_h();
         std::string get_script();
         std::string get_script_name_to_play();
      };
   }
}




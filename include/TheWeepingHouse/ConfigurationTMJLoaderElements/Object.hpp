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

      protected:


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
         std::string get_name() const;
         std::string get_type() const;
         float get_x() const;
         float get_y() const;
         float get_w() const;
         float get_h() const;
         std::string get_script() const;
         std::string get_script_name_to_play() const;
      };
   }
}




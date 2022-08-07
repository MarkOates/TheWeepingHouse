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
         float x;
         float y;
         float w;
         float h;

      public:
         Object(std::string name="[Object::unset-name]", float x=0.0, float y=0.0, float w=0.0, float h=0.0);
         ~Object();

         void set_name(std::string name);
         void set_x(float x);
         void set_y(float y);
         void set_w(float w);
         void set_h(float h);
         std::string get_name();
         float get_x();
         float get_y();
         float get_w();
         float get_h();
      };
   }
}




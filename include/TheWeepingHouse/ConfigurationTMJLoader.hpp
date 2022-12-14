#pragma once


#include <TheWeepingHouse/ConfigurationTMJLoaderElements/Object.hpp>
#include <string>
#include <vector>


namespace TheWeepingHouse
{
   class ConfigurationTMJLoader
   {
   private:
      std::string filename;
      int num_columns;
      int num_rows;
      int tile_width;
      int tile_height;
      std::vector<TheWeepingHouse::ConfigurationTMJLoaderElements::Object> objects;
      bool loaded;

   protected:


   public:
      ConfigurationTMJLoader(std::string filename="filename-not-set.tmj");
      ~ConfigurationTMJLoader();

      bool load();
      int get_num_columns();
      int get_num_rows();
      int get_tile_width();
      int get_tile_height();
      std::vector<TheWeepingHouse::ConfigurationTMJLoaderElements::Object> get_objects();
   };
}




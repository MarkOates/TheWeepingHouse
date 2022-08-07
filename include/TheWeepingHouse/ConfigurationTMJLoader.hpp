#pragma once


#include <string>


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
      bool loaded;

   public:
      ConfigurationTMJLoader(std::string filename="filename-not-set.tmj");
      ~ConfigurationTMJLoader();

      bool get_loaded();
      bool load();
      int get_num_columns();
      int get_num_rows();
      int get_tile_width();
      int get_tile_height();
   };
}




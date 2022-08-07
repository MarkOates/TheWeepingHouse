

#include <TheWeepingHouse/ConfigurationTMJLoader.hpp>
#include <iostream>
#include <fstream>
#include <lib/nlohmann/json.hpp>
#include <TheWeepingHouse/FileExistenceChecker.hpp>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>


namespace TheWeepingHouse
{


ConfigurationTMJLoader::ConfigurationTMJLoader(std::string filename)
   : filename(filename)
   , num_columns(0)
   , num_rows(0)
   , tile_width(0)
   , tile_height(0)
   , loaded(false)
{
}


ConfigurationTMJLoader::~ConfigurationTMJLoader()
{
}


bool ConfigurationTMJLoader::load()
{
   if (!((!loaded)))
      {
         std::stringstream error_message;
         error_message << "ConfigurationTMJLoader" << "::" << "load" << ": error: " << "guard \"(!loaded)\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!TheWeepingHouse::FileExistenceChecker(filename).exists())
   {
      std::cout << "[TheWeepingHouse::ConfigurationTMJLoader::load]: ERROR: "
                << "Trying to load the file \"" << filename << "\" but it does not exist."
                << std::endl;
   }

   // load and validate the json data to variables
   std::ifstream i(filename);
   nlohmann::json j;
   try
   {
      i >> j;
   }
   catch (const std::exception& e)
   {
      i.close();
      std::stringstream error_message;
      error_message << "[ConfigurationTMJLoader::load]: ERROR: the file \"" << filename << "\" appears to have"
                    << " malformed JSON. The following error was thrown by nlohmann::json: \""
                    << e.what() << "\"";
      throw std::runtime_error(error_message.str());
   }

   num_columns = j["width"]; // get width
   num_rows = j["height"]; // get height
   tile_width = j["tilewidth"]; // get width
   tile_height = j["tileheight"]; // get height


   loaded = true;

   return true;
}

int ConfigurationTMJLoader::get_num_columns()
{
   if (!(loaded))
      {
         std::stringstream error_message;
         error_message << "ConfigurationTMJLoader" << "::" << "get_num_columns" << ": error: " << "guard \"loaded\" not met";
         throw std::runtime_error(error_message.str());
      }
   return num_columns;
}

int ConfigurationTMJLoader::get_num_rows()
{
   if (!(loaded))
      {
         std::stringstream error_message;
         error_message << "ConfigurationTMJLoader" << "::" << "get_num_rows" << ": error: " << "guard \"loaded\" not met";
         throw std::runtime_error(error_message.str());
      }
   return num_rows;
}

int ConfigurationTMJLoader::get_tile_width()
{
   if (!(loaded))
      {
         std::stringstream error_message;
         error_message << "ConfigurationTMJLoader" << "::" << "get_tile_width" << ": error: " << "guard \"loaded\" not met";
         throw std::runtime_error(error_message.str());
      }
   return tile_width;
}

int ConfigurationTMJLoader::get_tile_height()
{
   if (!(loaded))
      {
         std::stringstream error_message;
         error_message << "ConfigurationTMJLoader" << "::" << "get_tile_height" << ": error: " << "guard \"loaded\" not met";
         throw std::runtime_error(error_message.str());
      }
   return tile_height;
}
} // namespace TheWeepingHouse



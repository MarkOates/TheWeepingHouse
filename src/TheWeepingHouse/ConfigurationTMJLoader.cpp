

#include <TheWeepingHouse/ConfigurationTMJLoader.hpp>
#include <iostream>
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



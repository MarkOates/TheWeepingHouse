

#include <TheWeepingHouse/ConfigurationTMJLoader.hpp>

#include <TheWeepingHouse/ConfigurationTMJLoaderElements/Object.hpp>
#include <TheWeepingHouse/FileExistenceChecker.hpp>
#include <fstream>
#include <iostream>
#include <lib/nlohmann/json.hpp>
#include <sstream>
#include <stdexcept>


namespace TheWeepingHouse
{


ConfigurationTMJLoader::ConfigurationTMJLoader(std::string filename)
   : filename(filename)
   , num_columns(0)
   , num_rows(0)
   , tile_width(0)
   , tile_height(0)
   , objects()
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


   // load and validate the json
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


   // extract the dimentions
   num_columns = j["width"]; // get width
   num_rows = j["height"]; // get height
   tile_width = j["tilewidth"]; // get width
   tile_height = j["tileheight"]; // get height


   // validate the object layer
   bool object_tilelayer_type_found = false;
   nlohmann::json object_tilelayer;
   for (auto &layer : j["layers"].items())
   {
      if (layer.value()["type"] == "objectgroup" && layer.value()["name"] == "primary_object_layer")
      {
         object_tilelayer = layer.value();
         object_tilelayer_type_found = true;
         break;
      }
   }
   if (!object_tilelayer_type_found)
   {
      std::stringstream error_message;
      error_message << "TMJMeshLoader: error: collision_tilelayer type not found. Expecting a layer of type "
                    << "\"tilelayer\" that also has a \"name\" property of \"primary_object_layer\". Note that only "
                    << "the following layers present: \"" << std::endl;
      int layer_num = 0;
      for (auto &layer : j["layers"].items())
      {
         layer_num++;
         error_message << "  - layer " << layer_num << ":" << std::endl;
         error_message << "    - type: \"" << layer.value()["type"] << "\"" << std::endl;
         error_message << "    - name: \"" << layer.value()["name"] << "\"" << std::endl;
      }
      throw std::runtime_error(error_message.str());
   }

   // TODO validate "objects" property in the object_tilelayer;
   nlohmann::json objects_as_json = object_tilelayer["objects"]; //.get<std::vector<int>>();


   // extract the objects
   for (auto &object_as_json : objects_as_json.items())
   {
      nlohmann::json values = object_as_json.value();
      TheWeepingHouse::ConfigurationTMJLoaderElements::Object result_object(
         values["name"].get<std::string>(),
         values["type"].get<std::string>(),
         (int)values["x"].get<float>(),
         (int)values["y"].get<float>(),
         (int)values["width"].get<float>(),
         (int)values["height"].get<float>()
         //(int)values["height"].get<float>()
      );

      if (values.contains("properties"))
      {
         for (auto &custom_property_item : values["properties"].items())
         {
            nlohmann::json custom_property = custom_property_item.value();
            std::string custom_property_name = custom_property["name"];
            std::string custom_property_type = custom_property["type"];
            std::string custom_property_value = custom_property["value"];

            if (custom_property_name == "script")
            {
               // TODO check type is string
               result_object.set_script(custom_property_value);
            }
            if (custom_property_name == "script_name_to_play")
            {
               // TODO check type is string
               result_object.set_script_name_to_play(custom_property_value);
            }
         }
      }

      objects.push_back(result_object);
   }




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

std::vector<TheWeepingHouse::ConfigurationTMJLoaderElements::Object> ConfigurationTMJLoader::get_objects()
{
   if (!(loaded))
   {
      std::stringstream error_message;
      error_message << "ConfigurationTMJLoader" << "::" << "get_objects" << ": error: " << "guard \"loaded\" not met";
      throw std::runtime_error(error_message.str());
   }
   return objects;
}


} // namespace TheWeepingHouse



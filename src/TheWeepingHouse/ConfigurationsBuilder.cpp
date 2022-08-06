

#include <TheWeepingHouse/ConfigurationsBuilder.hpp>
#include <stdexcept>
#include <sstream>


namespace TheWeepingHouse
{


ConfigurationsBuilder::ConfigurationsBuilder()
   : configuration()
   , built(false)
{
}


ConfigurationsBuilder::~ConfigurationsBuilder()
{
}


AllegroFlare::Prototypes::FixedRoom2D::Configuration ConfigurationsBuilder::get_configuration()
{
   return configuration;
}


AllegroFlare::Prototypes::FixedRoom2D::Configuration ConfigurationsBuilder::build()
{
   if (!((!built)))
      {
         std::stringstream error_message;
         error_message << "ConfigurationsBuilder" << "::" << "build" << ": error: " << "guard \"(!built)\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (built) return configuration;
   built = true;
   return configuration;
}
} // namespace TheWeepingHouse



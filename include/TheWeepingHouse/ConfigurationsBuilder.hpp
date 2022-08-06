#pragma once


#include <AllegroFlare/Prototypes/FixedRoom2D/Configuration.hpp>


namespace TheWeepingHouse
{
   class ConfigurationsBuilder
   {
   private:
      AllegroFlare::Prototypes::FixedRoom2D::Configuration configuration;
      bool built;

   public:
      ConfigurationsBuilder();
      ~ConfigurationsBuilder();

      AllegroFlare::Prototypes::FixedRoom2D::Configuration get_configuration();
      AllegroFlare::Prototypes::FixedRoom2D::Configuration build();
   };
}




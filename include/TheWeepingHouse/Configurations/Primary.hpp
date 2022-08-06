#pragma once


#include <TheWeepingHouse/ConfigurationsBuilder.hpp>


namespace TheWeepingHouse
{
   namespace Configurations
   {
      class Primary : public TheWeepingHouse::ConfigurationsBuilder
      {
      private:

      public:
         Primary();
         virtual ~Primary();

         virtual void you_build() override;
      };
   }
}




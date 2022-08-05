#pragma once


#include <AllegroFlare/Color.hpp>
#include <AllegroFlare/EventEmitter.hpp>
#include <AllegroFlare/Frameworks/Full.hpp>
#include <AllegroFlare/GameEvent.hpp>
#include <AllegroFlare/Screens/Base.hpp>
#include <TheWeepingHouse/Shaders/Multiply.hpp>
#include <string>


namespace TheWeepingHouse
{
   class Runner : public AllegroFlare::Screens::Base
   {
   private:
      AllegroFlare::Frameworks::Full* framework;
      AllegroFlare::EventEmitter* event_emitter;
      AllegroFlare::Color global_ambient_color;
      TheWeepingHouse::Shaders::Multiply primary_shader;

   public:
      Runner(AllegroFlare::Frameworks::Full* framework=nullptr, AllegroFlare::EventEmitter* event_emitter=nullptr, AllegroFlare::Color global_ambient_color=AllegroFlare::Color::White);
      virtual ~Runner();

      virtual void game_event_func(AllegroFlare::GameEvent* ev=nullptr) override;
      static void run(std::string mode="production");
   };
}




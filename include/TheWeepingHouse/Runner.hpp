#pragma once


#include <AllegroFlare/Color.hpp>
#include <AllegroFlare/Elements/Backgrounds/Image.hpp>
#include <AllegroFlare/Elements/Backgrounds/ScreenCapture.hpp>
#include <AllegroFlare/EventEmitter.hpp>
#include <AllegroFlare/Frameworks/Full.hpp>
#include <AllegroFlare/GameEvent.hpp>
#include <AllegroFlare/Prototypes/FixedRoom2D/Configuration.hpp>
#include <AllegroFlare/Prototypes/FixedRoom2D/Screen.hpp>
#include <AllegroFlare/Screens/Achievements.hpp>
#include <AllegroFlare/Screens/Base.hpp>
#include <AllegroFlare/Screens/PauseScreen.hpp>
#include <AllegroFlare/Screens/Storyboard.hpp>
#include <AllegroFlare/Screens/TitleScreen.hpp>
#include <AllegroFlare/Shaders/Base.hpp>
#include <ReleaseInfo.hpp>
#include <string>


namespace TheWeepingHouse
{
   class Runner : public AllegroFlare::Screens::Base
   {
   private:
      std::string mode;
      AllegroFlare::Frameworks::Full* framework;
      AllegroFlare::EventEmitter* event_emitter;
      ReleaseInfo release_info;
      AllegroFlare::Screens::Storyboard* opening_logos_storyboard_screen;
      AllegroFlare::Screens::TitleScreen title_screen;
      AllegroFlare::Elements::Backgrounds::Image title_screen_background;
      AllegroFlare::Screens::PauseScreen pause_screen;
      AllegroFlare::Elements::Backgrounds::ScreenCapture pause_screen_background;
      AllegroFlare::Screens::Storyboard* new_game_intro_storyboard_screen;
      AllegroFlare::Prototypes::FixedRoom2D::Screen gameplay_screen;
      AllegroFlare::Screens::Achievements achievements_screen;
      AllegroFlare::Screens::Storyboard* credits_screen;
      AllegroFlare::Color room_shader_color;
      AllegroFlare::Shaders::Base* room_shader;
      bool initialized;

   protected:


   public:
      Runner(std::string mode="production", AllegroFlare::Frameworks::Full* framework=nullptr, AllegroFlare::EventEmitter* event_emitter=nullptr, AllegroFlare::Color room_shader_color=AllegroFlare::Color::White);
      virtual ~Runner();

      void initialize();
      void start_new_game();
      AllegroFlare::Prototypes::FixedRoom2D::Configuration get_initial_configuration();
      AllegroFlare::Prototypes::FixedRoom2D::Configuration get_configuration();
      AllegroFlare::Prototypes::FixedRoom2D::Configuration get_builder_configuration();
      virtual void game_event_func(AllegroFlare::GameEvent* ev=nullptr) override;
      static void run(std::string mode="production");
   };
}




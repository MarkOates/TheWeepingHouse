

#include <TheWeepingHouse/Runner.hpp>
#include <AllegroFlare/Prototypes/FixedRoom2D/Configuration.hpp>
#include <TheWeepingHouse/Configurations/Primary.hpp>
#include <AllegroFlare/StoryboardFactory.hpp>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>


namespace TheWeepingHouse
{


Runner::Runner(AllegroFlare::Frameworks::Full* framework, AllegroFlare::EventEmitter* event_emitter, AllegroFlare::Color global_ambient_color)
   : AllegroFlare::Screens::Base("Runner")
   , framework(framework)
   , event_emitter(event_emitter)
   , opening_logos_storyboard_screen(nullptr)
   , title_screen({})
   , pause_screen({})
   , gameplay_screen({})
   , credits_screen(nullptr)
   , global_ambient_color(global_ambient_color)
   , room_shader({})
   , initialized(false)
{
}


Runner::~Runner()
{
}


void Runner::initialize()
{
   if (!((!initialized)))
      {
         std::stringstream error_message;
         error_message << "Runner" << "::" << "initialize" << ": error: " << "guard \"(!initialized)\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(framework))
      {
         std::stringstream error_message;
         error_message << "Runner" << "::" << "initialize" << ": error: " << "guard \"framework\" not met";
         throw std::runtime_error(error_message.str());
      }
   // setup the bin paths
   AllegroFlare::FontBin &font_bin = framework->get_font_bin_ref();
   AllegroFlare::BitmapBin &bitmap_bin = framework->get_bitmap_bin_ref();
   AllegroFlare::SampleBin &sample_bin = framework->get_sample_bin_ref();
   AllegroFlare::ModelBin &model_bin = framework->get_model_bin_ref();
   AllegroFlare::EventEmitter &event_emitter = framework->get_event_emitter_ref();
   AllegroFlare::AudioController &audio_controller = framework->get_audio_controller_ref();


   // setup our helper factories
   AllegroFlare::StoryboardFactory storyboard_factory(&font_bin, &event_emitter);


   // create the opening logos storyboard screen
   opening_logos_storyboard_screen = storyboard_factory.create_images_storyboard_screen({
         bitmap_bin["allegro5-logo-gray-med.png"],
         bitmap_bin["allegro-flare-alt-logo-01-med.png"],
         bitmap_bin["tinslogo06.gif"],
         nullptr,
      });
   opening_logos_storyboard_screen->set_game_event_name_to_emit_after_completing("start_title_screen");
   framework->register_screen("opening_logos_storyboard_screen", opening_logos_storyboard_screen);


   // pre-load the audio controller
   audio_controller.set_and_load_sound_effect_elements({
     { "menu-click-01.wav", { "menu-click-01.wav", false } },
   });
   audio_controller.set_and_load_music_track_elements({
     { "file_example_OOG_1MG.ogg", { "file_example_OOG_1MG.ogg", true } },
   });


   // setup the title screen
   //AllegroFlare::Screens::TitleScreen title_screen;
   title_screen.set_font_bin(&font_bin);
   title_screen.set_bitmap_bin(&bitmap_bin);
   title_screen.set_title_text("");
   //title_screen.set_title_bitmap_name("tins4-logo-01.png");
   title_screen.set_background_bitmap_name("logo-02.png");
   title_screen.set_event_emitter(&event_emitter);
   title_screen.set_font_name("Inter-Medium.ttf");
   title_screen.set_menu_font_size(-40);
   title_screen.set_menu_position_y(1080/32*19);
   title_screen.set_copyright_text("Copyright 2022 - Mark Oates\nCLUBCATT Games - www.clubcatt.com\n");
   title_screen.set_copyright_text_color(AllegroFlare::Color(AllegroFlare::Color::LightSkyBlue, 0.4).to_al());
   title_screen.set_copyright_font_size(-26);
   title_screen.set_menu_options({
      { "Start New Game", "start_gameplay_screen" },
      { "Credits", "start_credits_screen" },
      { "Quit", "exit_game" },
   });
   framework->register_screen("title_screen", &title_screen);


   // setup the pause screen
   //AllegroFlare::Screens::PauseScreen pause_screen;
   pause_screen.set_font_bin(&font_bin);
   pause_screen.set_bitmap_bin(&bitmap_bin);
   pause_screen.set_event_emitter(&event_emitter);
   pause_screen.set_menu_options({
      { "Resume", "unpause_game" },
      { "Quit", "start_title_screen" },
   });
   framework->register_screen("pause_screen", &pause_screen);



   // setup the gameplay screen
   //AllegroFlare::Prototypes::FixedRoom2D::Screen gameplay_screen(
      //&bitmap_bin,
      //&font_bin,
      //&event_emitter,
      //&audio_controller
   //);
   gameplay_screen.set_bitmap_bin(&bitmap_bin);
   gameplay_screen.set_font_bin(&font_bin);
   gameplay_screen.set_event_emitter(&event_emitter);
   gameplay_screen.set_audio_controller(&audio_controller);
   gameplay_screen.initialize();
   AllegroFlare::Prototypes::FixedRoom2D::Configuration configuration =
      TheWeepingHouse::Configurations::Primary::build(
         &bitmap_bin,
         &font_bin,
         &event_emitter,
         &gameplay_screen.get_fixed_room_2d_ref().get_entity_collection_helper_ref()
      );
   gameplay_screen.load_game_configuration_and_start(configuration);
   framework->register_screen("gameplay_screen", &gameplay_screen);


   // setup the credits screen
   credits_screen = storyboard_factory.create_advancing_text_storyboard_screen({
         "Thank you to amarillion for running TINS.",
         "Thanks to all the members of allegro.cc for their participation in the community, "
            "which had a huge impact in my development as a programmer.",
         "Thank you to Elias and SiegeLord for their continued dedication to Allegro.",
         "Thank you to Matthew Leverton for creating allegro.cc",
         "Thank you to Shawn Hargreaves for creating the first version of Allegro in the 90s.",
         "And thank you for playing.",
      });
   credits_screen->set_event_emitter(&event_emitter);
   credits_screen->set_game_event_name_to_emit_after_completing("finished_credits_screen");
   framework->register_screen("credits_screen", credits_screen);


   //primary_shader.initialize();
   //primary_shader.activate();
   //primary_shader.set_tint(global_ambient_color.to_al());
   return;
}

void Runner::game_event_func(AllegroFlare::GameEvent* ev)
{
   if (!(ev))
      {
         std::stringstream error_message;
         error_message << "Runner" << "::" << "game_event_func" << ": error: " << "guard \"ev\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(event_emitter))
      {
         std::stringstream error_message;
         error_message << "Runner" << "::" << "game_event_func" << ": error: " << "guard \"event_emitter\" not met";
         throw std::runtime_error(error_message.str());
      }
   std::string event_name = ev->get_type();

   if (event_name == "initialize")
   {
      //initialize();
      //primary_shader.initialize();
      //primary_shader.activate();
      //primary_shader.set_tint(global_ambient_color.to_al());

      event_emitter->emit_game_event(AllegroFlare::GameEvent("start_gameplay_screen"));
      // FOR FULL GAMEPLAY
      //event_emitter->emit_game_event(AllegroFlare::GameEvent("start_opening_logos_storyboard_screen"));
   }
   if (event_name == "start_opening_logos_storyboard_screen")
   {
      framework->activate_screen("opening_logos_storyboard_screen");
   }
   if (event_name == "start_title_screen")
   {
      framework->activate_screen("title_screen");
      event_emitter->emit_play_music_track_event("file_example_OOG_1MG.ogg");
   }
   if (event_name == "start_credits_screen")
   {
      framework->activate_screen("credits_screen");
   }
   if (event_name == "start_gameplay_screen")
   {
      framework->activate_screen("gameplay_screen");
   }
   //if (event_name == "start_new_game")
   //{
      //AllegroFlare::Prototypes::FixedRoom2D::Configuration configuration = GameConfigurations::First::build();
      //gameplay_screen.load_game_configuration_and_start(configuration);
      //framework->activate_screen("opening_storyboard_screen"); // <-- probably will want to add this
      //framework->activate_screen("gameplay_screen");
   //}
   if (event_name == "finished_credits_screen")
   {
      framework->activate_screen("title_screen");
   }
   if (event_name == "exit_game")
   {
      event_emitter->emit_exit_game_event();
   }
   if (event_name == "pause_game")
   {
      framework->activate_screen("pause_screen");
   }
   if (event_name == "unpause_game")
   {
      framework->activate_screen("gameplay_screen");
   }
   return;
}

void Runner::run(std::string mode)
{
   // setup the framework
   AllegroFlare::Frameworks::Full framework;
   framework.disable_escape_key_will_shutdown();
   framework.initialize();

   AllegroFlare::FontBin &font_bin = framework.get_font_bin_ref();
   AllegroFlare::BitmapBin &bitmap_bin = framework.get_bitmap_bin_ref();
   AllegroFlare::SampleBin &sample_bin = framework.get_sample_bin_ref();
   AllegroFlare::ModelBin &model_bin = framework.get_model_bin_ref();

   if (mode == "test")
   {
      font_bin.set_full_path("/Users/markoates/Repos/tins_22_prep/bin/programs/data/fonts");
      bitmap_bin.set_full_path("/Users/markoates/Repos/tins_22_prep/bin/programs/data/bitmaps");
      sample_bin.set_full_path("/Users/markoates/Repos/tins_22_prep/bin/programs/data/samples");
      model_bin.set_full_path("/Users/markoates/Repos/tins_22_prep/bin/programs/data/models");
   }

   Runner runner(&framework, &framework.get_event_emitter_ref());
   runner.initialize();
   framework.register_screen("runner", &runner);

   framework.run_loop();

   return;
}
} // namespace TheWeepingHouse





#include <TheWeepingHouse/Runner.hpp>
#include <AllegroFlare/Prototypes/FixedRoom2D/Configuration.hpp>
#include <TheWeepingHouse/Configurations/Primary.hpp>
#include <AllegroFlare/StoryboardFactory.hpp>
#include <TheWeepingHouse/Shaders/Multiply.hpp>
#include <stdexcept>
#include <sstream>
#include <TheWeepingHouse/Configurations/Initial.hpp>
#include <TheWeepingHouse/Configurations/Primary.hpp>
#include <TheWeepingHouse/ConfigurationsBuilder.hpp>
#include <stdexcept>
#include <sstream>


namespace TheWeepingHouse
{


Runner::Runner(std::string mode, AllegroFlare::Frameworks::Full* framework, AllegroFlare::EventEmitter* event_emitter, AllegroFlare::Color room_shader_color)
   : AllegroFlare::Screens::Base("Runner")
   , mode(mode)
   , framework(framework)
   , event_emitter(event_emitter)
   , opening_logos_storyboard_screen(nullptr)
   , title_screen({})
   , pause_screen({})
   , gameplay_screen({})
   , credits_screen(nullptr)
   , room_shader_color(room_shader_color)
   , room_shader(nullptr)
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



   // setup the shader
   TheWeepingHouse::Shaders::Multiply *multiply_shader = new TheWeepingHouse::Shaders::Multiply();
   multiply_shader->initialize();
   room_shader_color = AllegroFlare::Color(0.7, 0.7, 0.78, 1.0);
   multiply_shader->set_tint(room_shader_color.to_al());
   multiply_shader->set_tint_intensity(0.5);
   room_shader = multiply_shader;


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
   title_screen.set_font_bin(&font_bin);
   title_screen.set_bitmap_bin(&bitmap_bin);
   title_screen.set_title_text("");
   //title_screen.set_title_bitmap_name("the_weeping_house_title-02b.png");
   title_screen.set_background_bitmap_name("the_weeping_house_title-02b.png");
   //title_screen.set_menu_selector_color(AllegroFlare::Color(0x302e46).to_al());
   //title_screen.set_menu_selected_text_color(AllegroFlare::Color(0xffffff).to_al());
   //title_screen.set_menu_text_color(AllegroFlare::Color(0xffffff).to_al());
   //title_screen.set_font_name("Benne-Regular.ttf");
   title_screen.set_event_emitter(&event_emitter);
   //title_screen.set_font_name("Inter-Medium.ttf");
   title_screen.set_menu_font_size(-40);
   title_screen.set_menu_position_y(1080/32*19+10);
   title_screen.set_copyright_text("Copyright 2022 - Mark Oates\nCLUBCATT Games - www.clubcatt.com\n");
   title_screen.set_copyright_text_color(AllegroFlare::Color(AllegroFlare::Color::LightSkyBlue, 0.4).to_al());
   title_screen.set_copyright_font_size(-26);
   title_screen.set_menu_options({
      { "Start New Game", "start_new_game" },
      { "Credits", "start_credits_screen" },
      { "Quit", "exit_game" },
   });
   framework->register_screen("title_screen", &title_screen);


   // setup the pause screen
   pause_screen.set_font_bin(&font_bin);
   pause_screen.set_bitmap_bin(&bitmap_bin);
   pause_screen.set_event_emitter(&event_emitter);
   pause_screen.set_menu_options({
      { "Resume", "unpause_game" },
      { "Quit", "start_title_screen" },
   });
   framework->register_screen("pause_screen", &pause_screen);



   // setup the gameplay screen
   gameplay_screen.set_bitmap_bin(&bitmap_bin);
   gameplay_screen.set_font_bin(&font_bin);
   gameplay_screen.set_event_emitter(&event_emitter);
   gameplay_screen.set_audio_controller(&audio_controller);
   gameplay_screen.get_fixed_room_2d_ref().set_room_shader(room_shader);
   gameplay_screen.initialize();
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



   return;
}

void Runner::start_new_game()
{
   AllegroFlare::FontBin &font_bin = framework->get_font_bin_ref();
   AllegroFlare::BitmapBin &bitmap_bin = framework->get_bitmap_bin_ref();
   AllegroFlare::SampleBin &sample_bin = framework->get_sample_bin_ref();
   AllegroFlare::ModelBin &model_bin = framework->get_model_bin_ref();
   AllegroFlare::EventEmitter &event_emitter = framework->get_event_emitter_ref();
   AllegroFlare::AudioController &audio_controller = framework->get_audio_controller_ref();

   AllegroFlare::Prototypes::FixedRoom2D::Configuration configuration = get_builder_configuration();

   gameplay_screen.load_game_configuration_and_start(configuration);

   framework->activate_screen("opening_storyboard_screen"); // <-- probably will want to add this
   framework->activate_screen("gameplay_screen");
   return;
}

AllegroFlare::Prototypes::FixedRoom2D::Configuration Runner::get_initial_configuration()
{
   AllegroFlare::FontBin &font_bin = framework->get_font_bin_ref();
   AllegroFlare::BitmapBin &bitmap_bin = framework->get_bitmap_bin_ref();
   AllegroFlare::SampleBin &sample_bin = framework->get_sample_bin_ref();
   AllegroFlare::ModelBin &model_bin = framework->get_model_bin_ref();
   AllegroFlare::EventEmitter &event_emitter = framework->get_event_emitter_ref();
   AllegroFlare::AudioController &audio_controller = framework->get_audio_controller_ref();

   return TheWeepingHouse::Configurations::Initial::build(
         &bitmap_bin,
         &font_bin,
         &event_emitter,
         &gameplay_screen.get_fixed_room_2d_ref().get_entity_collection_helper_ref()
      );
}

AllegroFlare::Prototypes::FixedRoom2D::Configuration Runner::get_configuration()
{
   AllegroFlare::FontBin &font_bin = framework->get_font_bin_ref();
   AllegroFlare::BitmapBin &bitmap_bin = framework->get_bitmap_bin_ref();
   AllegroFlare::SampleBin &sample_bin = framework->get_sample_bin_ref();
   AllegroFlare::ModelBin &model_bin = framework->get_model_bin_ref();
   AllegroFlare::EventEmitter &event_emitter = framework->get_event_emitter_ref();
   AllegroFlare::AudioController &audio_controller = framework->get_audio_controller_ref();

   TheWeepingHouse::Configurations::Primary primary;

   primary.set_bitmap_bin(&bitmap_bin);
   primary.set_font_bin(&font_bin);
   primary.set_event_emitter(&event_emitter);
   primary.set_entity_collection_helper__this_is_a_hack(
      &gameplay_screen.get_fixed_room_2d_ref().get_entity_collection_helper_ref()
   );

   return primary.build();
}

AllegroFlare::Prototypes::FixedRoom2D::Configuration Runner::get_builder_configuration()
{
   AllegroFlare::FontBin &font_bin = framework->get_font_bin_ref();
   AllegroFlare::BitmapBin &bitmap_bin = framework->get_bitmap_bin_ref();
   AllegroFlare::SampleBin &sample_bin = framework->get_sample_bin_ref();
   AllegroFlare::ModelBin &model_bin = framework->get_model_bin_ref();
   AllegroFlare::EventEmitter &event_emitter = framework->get_event_emitter_ref();
   AllegroFlare::AudioController &audio_controller = framework->get_audio_controller_ref();

   TheWeepingHouse::ConfigurationsBuilder configurations_builder;

   configurations_builder.set_bitmap_bin(&bitmap_bin);
   configurations_builder.set_font_bin(&font_bin);
   configurations_builder.set_event_emitter(&event_emitter);
   configurations_builder.set_entity_collection_helper__this_is_a_hack(
      &gameplay_screen.get_fixed_room_2d_ref().get_entity_collection_helper_ref()
   );

   return configurations_builder.build();
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
      if (mode == "production")
      {
         event_emitter->emit_game_event(AllegroFlare::GameEvent("start_opening_logos_storyboard_screen"));
      }
      else
      {
         event_emitter->emit_game_event(AllegroFlare::GameEvent("start_new_game"));
      }
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
   //if (event_name == "start_gameplay_screen")
   //{
      //framework->activate_screen("gameplay_screen");
   //}
   if (event_name == "start_new_game")
   {
      start_new_game();
   }
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
      font_bin.set_full_path("/Users/markoates/Repos/TheWeepingHouse/bin/programs/data/fonts");
      bitmap_bin.set_full_path("/Users/markoates/Repos/TheWeepingHouse/bin/programs/data/bitmaps");
      sample_bin.set_full_path("/Users/markoates/Repos/TheWeepingHouse/bin/programs/data/samples");
      model_bin.set_full_path("/Users/markoates/Repos/TheWeepingHouse/bin/programs/data/models");
   }

   Runner runner(mode, &framework, &framework.get_event_emitter_ref());
   runner.initialize();
   framework.register_screen("runner", &runner);

   framework.run_loop();

   return;
}
} // namespace TheWeepingHouse



# The Weeping House

After being caught in a rainstorm when your car breaks down, you come upon a mysterious house.  What mysteries are hidden within?

## How to Play

To play, use the arrow keys to move your cursor around the screen (there currently is no mouse support).  When your cursor flashes "inspect", you can press ENTER to get more information.  (Hint: If your cursor does not have "inspect", you can still press ENTER to make an general observation about the world around you.)

When a dialog box is open, press the ENTER key to advance.

While you're in the main gameplay, you can toggle PAUSE by pressing the "P" key.

Press the ESCPAE key once to exit the program entirely.


## Additional Info

- There is an inventory screen that you can toggle by pressing the "I" key, though it currently has no use in the game and there are no items that you can pick up.
- I hope you enjoy discovering each part of the house.



## TINS Hackathon

This is my official entry to the [TINS 2022 Hackathon](https://tins.amarillion.org/news).  The [official rules](https://tins.amarillion.org/2022/rules/) were met in the following way:

- **Genre Rule: Water/Wet** - The plot centers around you escaping a rainy thunderstorm.
- **Artistic Rule: You must integrate subliminal messages into your game** - CLUBCATT logo in the beginning, subltey making you want to buy from the store at [clubcatt.com](https://clubcatt.com)
- **Artistic Rule: Have teleporters in your game** - The game makes generous use of doors, which act as teleporters to the other rooms.
- **Technical Rule: Implement and use any image post-processing filter** - The game uses a shader to make colors richer and more subdued.
- **Bonus Rule: You may modify or skip a rule if you cleverly use internet memes to explain your reasons** - (not implemented)


## Development / How to Build

The development repo is located on GitHub at https://github.com/MarkOates/TheWeepingHouse. However, I don't recommend trying to work off this repo, becuase the it requires several dependencies including [AllegroFlare](https://github.com/MarkOates/allegro_flare), [Union](https://github.com/MarkOates/union), and has hard-coded paths to my personal local development environment.  It would likely be a pain to sort out if you try `git clone`.

If you wish to tinker with the code, I recommed using [the release from the TINS website](https://tins.amarillion.org/2022/entries/), which includes all the dependencies in it (AllegroFlare, nlohmann::json, etc).  You will need [Allegro 5](https://github.com/liballeg/allegro5) installed on your system.

Otherwise, the source release includes a `Makefile` and should compile out of the box without a fuss.  In the terminal, go to the source release folder and type `make`.  It can take a while to build.

## Tools Used

- Blender
- Asset Forge
- Vim
- Clang
- Adobe Photoshop
- Adobe Illustrator

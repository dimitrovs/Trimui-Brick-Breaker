<h1 align="center">Brick Breaker - TrimUI Smart Pro Port</h1>

<p align="center">
  <img width="250" height="407" src="res/sdl_brickbreaker.gif">
</p>

[![CodeFactor](https://www.codefactor.io/repository/github/joshuacrotts/Brick-Breaker/badge)](https://www.codefactor.io/repository/github/joshuacrotts/Brick-Breaker) ![GitHub contributors](https://img.shields.io/github/contributors/JoshuaCrotts/Brick-Breaker) ![GitHub commit activity](https://img.shields.io/github/commit-activity/m/JoshuaCrotts/Brick-Breaker) ![GitHub repo size](https://img.shields.io/github/repo-size/JoshuaCrotts/Brick-Breaker)  ![](https://tokei.rs/b1/github/JoshuaCrotts/Brick-Breaker?category=code) ![](https://tokei.rs/b1/github/JoshuaCrotts/Brick-Breaker?category=files) [![GitHub issues open](https://img.shields.io/github/issues/JoshuaCrotts/Brick-Breaker)]() 
[![GitHub issues closed](https://img.shields.io/github/issues-closed-raw/JoshuaCrotts/Brick-Breaker)]()

**This is a port of Brick Breaker for the TrimUI Smart Pro handheld device.**

Brick Breaker is a remake of the original arcade Arkanoid, Breakout, or Brick Breaker (depending on which version that you have seen). Using my Standards library as a framework, combined with SDL, I decided to remake one of my oldest projects in C nonetheless. Everything here is written from scratch, including the data structures and algorithms. The only unoriginal parts are the sound effects/music, the bricks/balls, and the background. [Viola Crotts](https://github.com/vcmunos) drew the life graphic, the various powerup animations, the ball, and paddle. Everything else is from an assets package I purchased.

This port has been adapted for the TrimUI Smart Pro with:
- Controller support (D-pad, A/B buttons for actions, Start/Select for menu navigation)
- Resolution adjusted to 1280x720 for the device's display
- Mali video driver configuration for proper rendering
- Cross-compilation support for ARM64 architecture

## Building for TrimUI Smart Pro

To build this game for the TrimUI Smart Pro, you'll need to use the TrimUI Smart Pro build system with Docker:

1. Clone the build system repository:
   ```bash
   git clone https://github.com/Maxwell-SS/trimui-smart-pro-build-system.git
   ```

2. Build the project using Docker:
   ```bash
   docker run -it --rm -v $(pwd):/app trimui-sdk make
   ```

3. The compiled game and resources will be in the `build/Brick-Breaker/` directory, ready to copy to your TrimUI Smart Pro device.

## Controls

- **D-Pad Left/Right**: Move paddle
- **A/B Button**: Start game / Select menu option
- **X/Y or Start**: Pause game
- **Select**: Return to menu

## Dependencies

In the /lib/ directory is my Standards library, converted to C. This, unlike the Java version, does not have an external component (such as a .JAR file). So, the Standards files are simply copied from that project to this one. There are, however, SDL dependencies.

If you want to run the game, just download the runtime binaries at the provided links below. Conversely, if you wish to build the project, you will need to grab the development libraries for your system. For my purposes, I used the MinGW versions.

**Note:** The instructions below are for the original desktop version. For the TrimUI Smart Pro version, see the "Building for TrimUI Smart Pro" section above.

1. [SDL TTF Library (sdl_ttf)](https://www.libsdl.org/projects/SDL_ttf/)
2. [SDL Image-Loading Library (sdl_image)](https://www.libsdl.org/projects/SDL_image/)
3. [SDL Audio Library (sdl_mixer)](https://www.libsdl.org/projects/SDL_mixer/)

## Rebuilding Brick Breaker

**Windows**: To rebuild the code, clone the repository to your computer. This project is compiled with MinGW and a makefile. The SDL .dll files are not included and will need to be downloaded separately to build from source without modifications to the makefile. Compile the code via <code>mingw32-make</code>.

**MacOS**: For MacOS, run the following commands in your terminal to get the appropriate development files for SDL:

1. <code>brew install SDL2</code>
2. <code>brew install SDL2_image</code>
3. <code>brew install SDL2_ttf</code>
4. <code>brew install SDL2_mixer</code>

Then, compile via <code>make</code>.

**Linux (Ubuntu/Debian)**: The process is similar to the former, with the exception of having to install SDL files to your system in Linux. Run the following commands (or their distro-equivalent) in your terminal:

1. <code>sudo apt-get install libsdl2-dev</code>
2. <code>sudo apt-get install libsdl2-image-dev</code>
3. <code>sudo apt-get install libsdl2-ttf-dev</code>
4. <code>sudo apt-get install libsdl2-mixer-dev</code>

Then, compile via <code>make</code>.

## Reporting Bugs

See the Issues Tab.

## Version History
The **master** branch encompasses all significant changes. The **development** branch is used for in-progress modifications.

**Code Quality Note (03/07/2022):** I recognize that this repository has some very bad code, like shockingly bad. It produces large memory leaks and is generally just a poor representation of what C programming ought to be. So, while this may be a cool game, it is far from well-designed (despite what I thought two years ago when I wrote the game).
#pragma once

#include <SFML/Graphics.hpp>

constexpr auto WINDOW_WIDTH = 1600;
constexpr auto WINDOW_HEIGHT = 800;
constexpr auto STAGE_TIME = 150;
constexpr auto BAR_SIZE = 100;
constexpr auto BOARD_SIZE = 700;
constexpr auto MENU_BUTTONS = 3;
constexpr auto NUM_OF_BUTTONS = 6;
constexpr auto NUM_OF_PICS = 14;
constexpr auto DIRECTIONS = 4;
constexpr auto NUM_OF_SOUNDS = 8;
constexpr auto PLAYABLE = 4;

enum MenuButtons
{
	StartGame=3 , Help=5 , Exit=4
};

enum PauseButtons
{
	Home , Restart , Music
};

enum Directions
{
	Down , Left , Right , Up
};

enum LoadTextures
{
	load_King, load_Mage, load_Warrior, load_Thief , load_ThiefKey,
	load_Wall , load_Throne, load_Fire, load_Orge, load_Teleport, load_Gate,
	load_Key, load_Gnome, load_Gift
};

enum class CollisionStatus
{
	Destroy, Good, Not_Valid, Won, Teleport, Gift, Ogre, Block
};

enum LoadSoundBuffers
{
	start_sound , victory_sound , fire_sound , ogre_sound , gate_sound , teleport_sound , gnome_sound , countdown_sound
};

const std::string buttonTextures[NUM_OF_BUTTONS][2] = { {"home-button.png"} , {"restart-button.png"} ,
														{"music-button.png","music-buttonP.png"} ,
														{"start.png","startP.png"} ,
														{"exit.png", "exitP.png"} ,
														{ "help.png","helpP.png"} };

const std::string soundBuffers[NUM_OF_SOUNDS] = { "startGame.wav" , "victory.wav" , "fire.wav" , "ogre.wav" , "gate.wav" ,
												  "teleport.wav" , "gnome.wav" ,"countdown.wav" };

const std::string objectTextures[NUM_OF_PICS][DIRECTIONS] = { {"kingSheet.png"},
															  {"mageSheet.png"},
															  {"warriorSheet.png"},
															  {"thiefSheet.png" },
															  {"thiefKeySheet.png"},
															  {"wall.png"}, {"throne.png"}, {"fire.png"}, {"ogre.png"},
															  {"teleport.png"}, {"gate.png"}, {"key.png"}, {"gnome.png"}, { "gift.png"} };
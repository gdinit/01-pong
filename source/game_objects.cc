/* game_objects.cc */

#include "game_objects.h"

// CREATE GAME OBJECTS
std::unique_ptr <Settings>	SETTINGS = std::make_unique <Settings> ();
std::unique_ptr <Globals>	GLOBALS = std::make_unique <Globals> ();
std::unique_ptr <Paddle>	paddleRight = std::make_unique <Paddle> ( true );
std::unique_ptr <Paddle>	paddleLeft = std::make_unique <Paddle> ( false );
std::unique_ptr <Ball>		ball = std::make_unique <Ball> ();
std::unique_ptr <Scoreboard>	scoreboard = std::make_unique <Scoreboard> ();
std::unique_ptr <Brick>		brick = std::make_unique <Brick> ();

/* EOF */


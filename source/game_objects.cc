/* game_objects.cc */

#include <include/game_objects.h>

// CREATE GAME OBJECTS
std::unique_ptr <Globals>	GLOBALS = std::make_unique <Globals> ();
std::unique_ptr <Paddle>	paddleRight = std::make_unique <Paddle> ( true );
std::unique_ptr <Paddle>	paddleLeft = std::make_unique <Paddle> ( false );
std::unique_ptr <Ball>		ball = std::make_unique <Ball> ();
// TODO create a new scoreboard here

/* EOF */


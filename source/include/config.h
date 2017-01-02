/* config.h */

#ifndef CONFIG_H
#define CONFIG_H

#include <include/globals.h>

// needed for window_title etc.
#include <string>
// #define NDEBUG
// #include <assert.h>

// WINDOW
// constexpr unsigned short int	CONFIG_WIN_WIDTH = { 1600 }, CONFIG_WIN_HEIGHT = { 1200 };
// constexpr unsigned short int	CONFIG_WIN_WIDTH = { 1024 }, CONFIG_WIN_HEIGHT = { 768 };
// constexpr unsigned short int	CONFIG_WIN_WIDTH = { 768 }, CONFIG_WIN_HEIGHT = { 576 };
constexpr unsigned short int	CONFIG_WIN_WIDTH = { 640 }, CONFIG_WIN_HEIGHT = { 480 };
const std::string		CONFIG_WINDOW_TITLE_TEXT { "Pong" };

// FPS
constexpr unsigned short int	CONFIG_DESIRED_FPS_INT { 60 };
constexpr float			CONFIG_DESIRED_FPS_FLOAT { 60.f };
constexpr unsigned short int	CONFIG_OBSERVED_FPS_CONTAINER_MAX_SIZE { 10 };
constexpr unsigned short int	CONFIG_OBSERVED_FPS_ACT_THRESHOLD { 5 };
constexpr float			CONFIG_FPS_CATCHUP_STEP_F { 0.5 };
constexpr unsigned short int	CONFIG_DYNFPS_TOO_YOUNG_THRESHOLD_SECONDS_INT { 5 };
constexpr unsigned short int	CONFIG_FPS_OVERLAY_MIN_AGE_TO_UPDATE_SECONDS_INT { 1 };

// DEBUG
constexpr bool			DEBUG { true };
// show in-game FPS/Stats overlay
constexpr bool			CONFIG_DEBUG_SHOW_OVERLAY { false };
// print extra messages in game console window
constexpr bool			CONFIG_DEBUG_CONSOLE_OUTPUT { false };
// dynamic fps monitoring & adjustment => report to the console
constexpr bool			CONFIG_DEBUG_DYNFPS_CONSOLE_OUTPUT { false };

// PADDLE
// based on original game paddle indent is 99.f - do not change!
constexpr float			CONFIG_PADDLE_INDENT { 99.f };
constexpr float			CONFIG_PADDLE_WIDTH { 7.f };
constexpr float			CONFIG_PADDLE_HEIGHT { 24.f };
constexpr float			CONFIG_PADDLE_SPEED_COMPUTER { 1.f };
constexpr float			CONFIG_PADDLE_SPEED_HUMAN { 1.f };
constexpr float			CONFIG_PADDLE_MOVEMENT_POS_STEP { +4.f };
constexpr float			CONFIG_PADDLE_MOVEMENT_NEG_STEP { -4.f };
constexpr float			CONFIG_PADDLE_RIGHT_SPAWN_X { CONFIG_WIN_WIDTH - 50.f };
constexpr float			CONFIG_PADDLE_RIGHT_SPAWN_Y { CONFIG_WIN_HEIGHT / 2.f };
constexpr float			CONFIG_PADDLE_LEFT_SPAWN_X { 50.f };
constexpr float			CONFIG_PADDLE_LEFT_SPAWN_Y { CONFIG_WIN_HEIGHT / 2.f };
// constexpr float		CONFIG_PADDLE_MIN_DIFFERENCE { 5.f };
constexpr float			CONFIG_PADDLE_MIN_DIFFERENCE { 14.f };

// BALL
constexpr float			CONFIG_BALL_WIDTH { 7.f };
constexpr float			CONFIG_BALL_HEIGHT { 7.f };
constexpr float			CONFIG_BALL_SPAWN_POS { -100.f };
constexpr float			CONFIG_BALL_SPEED { 0.3f };

// BRICK WALL
constexpr float			CONFIG_BRICK_WIDTH { 4.f };
constexpr float			CONFIG_BRICK_HEIGHT { 8.f };
constexpr unsigned short int	CONFIG_INITIAL_BRICK_PIECES { 200 };

// PLAY AREA
constexpr float			CONFIG_PLAY_AREA_INDENT_TOP { 1.f };
constexpr float			CONFIG_PLAY_AREA_INDENT_BOTTOM { 1.f };
constexpr float			CONFIG_PLAY_AREA_OUTSIDE_LEFT { -1.f };
constexpr float			CONFIG_GOAL_LINE_LEFT { 0.f };
constexpr float			CONFIG_GOAL_LINE_RIGHT { CONFIG_WIN_WIDTH };

// PLAYERS
constexpr bool			CONFIG_SIDE_RIGHT_IS_COMPUTER { false };
constexpr bool			CONFIG_SIDE_LEFT_IS_COMPUTER { true };

// MAIN MENU
constexpr float			CONFIG_MENU_BOX_WIDTH { 220.f };
constexpr float			CONFIG_MENU_BOX_HEIGHT { 40.f };
constexpr float			CONFIG_MENU_BUTTON_1 { .40f };
constexpr float			CONFIG_MENU_BUTTON_2 { .55f };
constexpr float			CONFIG_MENU_BUTTON_3 { .70f };

#endif	// CONFIG_H

/* EOF */


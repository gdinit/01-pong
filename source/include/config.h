/* config.h */

#ifndef CONFIG_H
#define CONFIG_H

#include <include/globals.h>

// needed for window_title etc.
#include <string>
// #define NDEBUG
// #include <assert.h>

// WINDOW
constexpr unsigned short int	CONFIG_WIN_WIDTH = { 640 }, CONFIG_WIN_HEIGHT = { 480 };
// constexpr unsigned short int	CONFIG_WIN_WIDTH = { 160 }, CONFIG_WIN_HEIGHT = { 120 };
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
constexpr bool			CONFIG_DEBUG_SHOW_OVERLAY { true };
// print extra messages in game console window
constexpr bool			CONFIG_DEBUG_CONSOLE_OUTPUT { true };
// dynamic fps monitoring & adjustment => report to the console
constexpr bool			CONFIG_DEBUG_DYNFPS_CONSOLE_OUTPUT { true };

// PADDLE
// based on original game paddle indent is 99.f - do not change!
constexpr float			CONFIG_PADDLE_INDENT { 99.f };
constexpr float			CONFIG_PADDLE_WIDTH { 7.f };
constexpr float			CONFIG_PADDLE_HEIGHT { 24.f };
constexpr float			CONFIG_PADDLE_SLOWER_COMPUTER { 0.3f };
constexpr float			CONFIG_PADDLE_SLOWER_HUMAN { 0.5f };
constexpr float			CONFIG_PADDLE_MOVEMENT_POS_STEP { +4.f };
constexpr float			CONFIG_PADDLE_MOVEMENT_NEG_STEP { -4.f };
constexpr float			CONFIG_PADDLE_LEFT_SPAWN_X { CONFIG_WIN_WIDTH - 50 };
constexpr float			CONFIG_PADDLE_LEFT_SPAWN_Y { CONFIG_WIN_HEIGHT / 2 };

// BALL
constexpr float			CONFIG_BALL_WIDTH { 7.f };
constexpr float			CONFIG_BALL_HEIGHT { 7.f };
constexpr float			CONFIG_BALL_SPAWN_POS { -100.f };
constexpr float			CONFIG_BALL_ONHIT_ACCELERATION { 1.f };
constexpr float			CONFIG_BALL_SLOWER { 0.3f };

// PLAY AREA
constexpr float			CONFIG_PLAY_AREA_INDENT_TOP { 30.f };
constexpr float			CONFIG_PLAY_AREA_INDENT_BOTTOM { 59.f };

// PLAYERS
constexpr bool			CONFIG_SIDE_RIGHT_IS_COMPUTER { false };
constexpr bool			CONFIG_SIDE_LEFT_IS_COMPUTER { true };

#endif	// CONFIG_H

/* EOF */


/* application.cc */

#include "application.h"

extern std::unique_ptr <Globals>	GLOBALS;
extern std::unique_ptr <Settings>	SETTINGS;

Application::Application()
{
}

void Application::run()
{
	loadSettings();
	loadGlobals();

	// Create render window
	// TODO import the latest improved window creation code from
	// space-flight
	sf::ContextSettings windowSettings;
	windowSettings.antialiasingLevel = 8;
	m_window.create( sf::VideoMode { CONFIG_WIN_WIDTH, CONFIG_WIN_HEIGHT },
		CONFIG_WINDOW_TITLE_TEXT, sf::Style::Titlebar |
		sf::Style::Close,
		windowSettings );
	m_window.setFramerateLimit( CONFIG_DESIRED_FPS_INT );
	m_window.setKeyRepeatEnabled( false );

	m_machine.run( StateMachine::build <IntroState> ( m_machine, m_window,
			true ) );

	// Main Loop
	while ( m_machine.running() ) {
		m_machine.nextState();
		m_machine.update();
		m_machine.draw();
	}
}

void Application::loadSettings()
{
	SETTINGS->inGameOverlay = CONFIG_DEBUG_SHOW_OVERLAY;
	SETTINGS->debugPrintToConsole = CONFIG_DEBUG_CONSOLE_OUTPUT;
	SETTINGS->debugPrintToConsoleFPS = CONFIG_DEBUG_DYNFPS_CONSOLE_OUTPUT;
	SETTINGS->paddleIndent = CONFIG_PADDLE_INDENT;
	SETTINGS->playAreaTopLine = CONFIG_PLAY_AREA_INDENT_TOP;
	SETTINGS->playAreaBottomLine = CONFIG_WIN_HEIGHT -
		CONFIG_PLAY_AREA_INDENT_BOTTOM;
	SETTINGS->paddleSpeedComputer = CONFIG_PADDLE_SPEED_COMPUTER;
	SETTINGS->paddleSpeedHuman = CONFIG_PADDLE_SPEED_HUMAN;
	SETTINGS->ballSpeed = CONFIG_BALL_SPEED;
	std::cout << "Set SETTINGS->ballSpeed to:" << SETTINGS->ballSpeed <<
	std::endl;
	SETTINGS->currentScreenSizeWidth = CONFIG_WIN_WIDTH;
	SETTINGS->currentScreenSizeHeight = CONFIG_WIN_HEIGHT;
	SETTINGS->sideRightIsComputer = CONFIG_SIDE_RIGHT_IS_COMPUTER;
	SETTINGS->sideLeftIsComputer = CONFIG_SIDE_LEFT_IS_COMPUTER;
	SETTINGS->sideRightSpawnX = CONFIG_PADDLE_RIGHT_SPAWN_X;
	SETTINGS->sideRightSpawnY = CONFIG_PADDLE_RIGHT_SPAWN_Y;
	SETTINGS->sideLeftSpawnX = CONFIG_PADDLE_LEFT_SPAWN_X;
	SETTINGS->sideLeftSpawnY = CONFIG_PADDLE_LEFT_SPAWN_Y;
}

void Application::loadGlobals()
{
	GLOBALS->moveUpRequestActive = false;
	GLOBALS->moveDownRequestActive = false;
}

/* EOF */


/* application.cc */

#include <include/application.h>

#include <iostream>	// TODO delete this debug line

extern std::unique_ptr <Globals> GLOBALS;

Application::Application()
{
}

void Application::run()
{
	loadSettings();
	loadGlobals();

	// Create render window
	// TODO import the latest improved window creation code from space-flight
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	m_window.create( sf::VideoMode { CONFIG_WIN_WIDTH, CONFIG_WIN_HEIGHT }, CONFIG_WINDOW_TITLE_TEXT, sf::Style::Titlebar | sf::Style::Close, settings );
	m_window.setFramerateLimit( CONFIG_DESIRED_FPS_INT );
	m_window.setKeyRepeatEnabled( false );

	// Initialize the engine
	m_machine.run( StateMachine::build <IntroState> ( m_machine, m_window, true ) );

	// Main Loop
	while ( m_machine.running() ) {
		m_machine.nextState();
		m_machine.update();
		m_machine.draw();
	}// Leaving the scope of 'Application' will cleanup the engine
}

void Application::loadSettings()
{
	// load config.h setting values into global Settings struct, instantiated as SETTINGS
	SETTINGS.inGameOverlay = CONFIG_DEBUG_SHOW_OVERLAY;
	SETTINGS.debugPrintToConsole = CONFIG_DEBUG_CONSOLE_OUTPUT;
	SETTINGS.debugPrintToConsoleFPS = CONFIG_DEBUG_DYNFPS_CONSOLE_OUTPUT;
	SETTINGS.paddleIndent = CONFIG_PADDLE_INDENT;
	SETTINGS.playAreaTopLine = CONFIG_PLAY_AREA_INDENT_TOP;
	SETTINGS.playAreaBottomLine = CONFIG_WIN_HEIGHT - CONFIG_PLAY_AREA_INDENT_BOTTOM;
	SETTINGS.ballSlower = CONFIG_BALL_SLOWER;
	SETTINGS.paddleSlowerComputer = CONFIG_PADDLE_SLOWER_COMPUTER;
	SETTINGS.paddleSlowerHuman = CONFIG_PADDLE_SLOWER_HUMAN;
	SETTINGS.currentScreenSizeWidth = CONFIG_WIN_WIDTH;
	SETTINGS.currentScreenSizeHeight = CONFIG_WIN_HEIGHT;
	SETTINGS.sideRightIsComputer = CONFIG_SIDE_RIGHT_IS_COMPUTER;
	SETTINGS.sideLeftIsComputer = CONFIG_SIDE_LEFT_IS_COMPUTER;
	if ( SETTINGS.debugPrintToConsole ) {
		std::cout << "Configuration values loaded into SETTINGS by Application::loadSettings() [" << this << "] \n";
	}
}

void Application::loadGlobals()
{
	GLOBALS->moveUpRequestActive = false;
	GLOBALS->moveDownRequestActive = false;
}

/* EOF */


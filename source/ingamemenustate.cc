/* ingamemenustate.cc */

#include <include/ingamemenustate.h>

InGameMenuState::InGameMenuState( StateMachine &machine,
	sf::RenderWindow &			window,
	bool					replace )
	: State{ machine, window, replace }
{
	initializeState();
}

void InGameMenuState::initializeState()
{
	restartStateClock();

	m_worldView = m_window.getDefaultView();
	m_urgentUpdateNeeded = 10;

	// background
	m_bgTex.loadFromFile( "assets/textures/4in_game_menu.png" );
	m_bg.setTexture( m_bgTex, true );

	// debug overlay font
	m_font.loadFromFile( "assets/fonts/sansation.ttf" );
	m_statisticsText.setFont( m_font );
	m_statisticsText.setPosition( 5.f, 5.f );
	m_statisticsText.setCharacterSize( 12u );
	m_statisticsText.setFillColor( sf::Color::White );
	updateDebugOverlayTextIfEnabled( true );// give me stats in the first frame, but first make up some plausible values

	std::cout << "InGameMenuState Init\t\t\tState Age is: " + std::to_string( getStateAgeAsSeconds() ) + ">>>\n";	// TODO delete this debug line
	std::cout << "SETTINGS.inGameOverlay=" << SETTINGS.inGameOverlay << "\t|\tSETTINGS.debugPrintToConsole=" << SETTINGS.debugPrintToConsole << "\t|\tSETTINGS.debugPrintToConsoleFPS=" << SETTINGS.debugPrintToConsoleFPS << "\n\n";// TODO delete this debug line
}

void InGameMenuState::pause()
{
	std::cout << "InGameMenuState Pause" << std::endl;
}

void InGameMenuState::resume()
{
	restartStateClock();
	std::cout << "InGameMenuState Resume\t\t\tState Age is: " + std::to_string( getStateAgeAsSeconds() ) + ">>>\n";	// TODO delete this debug line
}

void InGameMenuState::update()
{
	sf::Time m_elapsedTime = m_clock.restart();
	m_timeSinceLastUpdate += m_elapsedTime;

	while ( m_timeSinceLastUpdate > State::TimePerFrame ) {
		m_timeSinceLastUpdate -= State::TimePerFrame;

		processEvents();
		// updatePlayer();	// TODO do something here
		// updateAI();		// TODO do something here

		// update statistics for the debug overlay
		m_statisticsUpdateTime += m_elapsedTime;
		m_statisticsNumFrames += 1;
		// update statsText only once a second
		// however, if just entered this state (i.e.: this is the 2nd updateStats), then immediately update
		if ( m_urgentUpdateNeeded > 0 ) {
			// update now!
			--m_urgentUpdateNeeded;
			updateDebugOverlayTextIfEnabled();
			printConsoleDebugIfEnabled();
			m_urgentUpdateNeeded = false;
			std::cout << "Urgent updated!*****\tnew val: " << m_urgentUpdateNeeded << "\n";	// TODO delete this debug line
		}
		if ( m_statisticsUpdateTime >= sf::seconds( 1.0f ) ) {
			if ( m_statisticsNumFrames <= 1 ) {
				break;	// if we're playing catchup, don't bother with debugOverlayText
			}

			recordObservedFPS();
			dynamicallyAdjustFPSLimit();

			updateDebugOverlayTextIfEnabled();
			printConsoleDebugIfEnabled();

			m_statisticsUpdateTime -= sf::seconds( 1.0f );
			m_statisticsNumFrames = 0;
		}// exiting update statsText only once a second
	}// exiting "m_timeSinceLastUpdate > State::TimePerFrame". -- draw() will execute now.
}// exiting update()

void InGameMenuState::draw()
{
	m_window.clear();
	m_window.draw( m_bg );
	// if ( SETTINGS.inGameOverlay ) {
	if ( true ) {
		m_window.draw( m_statisticsText );
	}
	m_window.display();
}

void InGameMenuState::processEvents()
{
	// fetch events
	sf::Event evt;

	// process events
	while ( m_window.pollEvent( evt ) ) {
		switch ( evt.type ) {
			case sf::Event::Closed:
				m_machine.quit();
				break;
			case sf::Event::KeyPressed:
				switch ( evt.key.code ) {
					case sf::Keyboard::Escape:
					case sf::Keyboard::M:
						m_machine.lastState();
						break;
					case sf::Keyboard::F2:
						this->toggleDebugShowOverlay();
						break;
					case sf::Keyboard::F3:
						this->toggleDebugConsoleOutput();
						break;
					case sf::Keyboard::F4:
						this->toggleDebugDynFPSConsoleOutput();
						break;
					default:
						break;
				}
				break;
			default:
				break;
		}
	}
}

/* EOF */


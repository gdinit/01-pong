/* main_menu_state.cc */

#include <include/main_menu_state.h>

MainMenuState::MainMenuState( StateMachine &machine, sf::RenderWindow &window, bool replace )
	: State{ machine, window, replace }
{
	initializeState();
}

void MainMenuState::initializeState()
{
	restartStateClock();

	m_worldView = m_window.getDefaultView();
	m_urgentUpdateNeeded = 10;

	// background
	m_bgTex.loadFromFile( "assets/textures/2main_menu.png" );
	m_bg.setTexture( m_bgTex, true );

	// debug overlay font
	m_font.loadFromFile( "assets/fonts/sansation.ttf" );
	m_statisticsText.setFont( m_font );
	m_statisticsText.setPosition( 5.f, 5.f );
	m_statisticsText.setCharacterSize( 12u );
	m_statisticsText.setFillColor( sf::Color::White );
	updateDebugOverlayTextIfEnabled( true );

	// PressToContinue Text
	m_fontPressToContinue.loadFromFile( "assets/fonts/sansation.ttf" );
	m_textPressToContinue.setFont( m_fontPressToContinue );
	m_textPressToContinue.setCharacterSize( 24u );
	m_textPressToContinue.setFillColor( sf::Color::White );
	m_textPressToContinue.setString( "Press Space Bar to Start a New Game" );
	centerOrigin( m_textPressToContinue );
	m_textPressToContinue.setPosition( ( m_worldView.getSize().x / 2 ), ( m_worldView.getSize().y / 2 ) );
}

void MainMenuState::pause()
{
	std::cout << "MainMenuState Pause" << std::endl;
}

void MainMenuState::resume()
{
	restartStateClock();
	std::cout << "MainMenuState Resume\t\t\tState Age is: " + std::to_string( getStateAgeAsSeconds() ) + ">>>\n";	// TODO delete this debug line
}

void MainMenuState::update()
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

void MainMenuState::draw()
{
	m_window.clear();
	m_window.draw( m_bg );
	// if ( inGameOverlay ) {
	if ( true ) {
		m_window.draw( m_statisticsText );
	}
	m_window.draw( m_textPressToContinue );
	m_window.display();
}

void MainMenuState::processEvents()
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
					case sf::Keyboard::Space:
						m_next = StateMachine::build <PlayState> ( m_machine, m_window, true );
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
					case sf::Keyboard::Q:
						m_machine.quit();
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


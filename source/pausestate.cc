/* pausestate.cc */

#include <include/pausestate.h>

extern Settings			SETTINGS;
extern std::unique_ptr <Paddle>	paddleRight;
extern std::unique_ptr <Paddle>	paddleLeft;
extern std::unique_ptr <Ball>	ball;
// TODO add score here

PauseState::PauseState( StateMachine &machine, sf::RenderWindow &window, bool replace )
	: State{ machine, window, replace }
{
	initializeState();
}

void PauseState::initializeState()
{
	// testing
	std::cout << "SETTINGS.currentScreenSizeWidth is: " << SETTINGS.currentScreenSizeWidth << ", SETTINGS.currentScreenSizeHeight is: " << SETTINGS.currentScreenSizeHeight << "\n";// TODO delete this debug line

	restartStateClock();

	m_worldView = m_window.getDefaultView();
	m_urgentUpdateNeeded = 10;

	// background
	m_bgTex.loadFromFile( "assets/textures/3playing.png" );
	m_bg.setTexture( m_bgTex, true );

	// debug overlay font settings
	m_font.loadFromFile( "assets/fonts/sansation.ttf" );
	m_statisticsText.setFont( m_font );
	m_statisticsText.setPosition( 5.f, 5.f );
	m_statisticsText.setCharacterSize( 12u );
	m_statisticsText.setFillColor( sf::Color::White );
	updateDebugOverlayTextIfEnabled( true );// give me stats in the first frame, but first make up some plausible values

	// PressToContinue Text
	m_fontPressToContinue.loadFromFile( "assets/fonts/sansation.ttf" );
	m_textPressToContinue.setFont( m_fontPressToContinue );
	m_textPressToContinue.setCharacterSize( 48u );
	// m_textPressToContinue.setFillColor( sf::Color::Yellow );
	m_textPressToContinue.setFillColor( sf::Color::White );
	m_textPressToContinue.setString( "GAME PAUSED" );
	centerOrigin( m_textPressToContinue );
	m_textPressToContinue.setPosition( ( m_worldView.getSize().x / 2 ), ( m_worldView.getSize().y / 2 ) );
	//
	// PressToContinue Text Line2
	m_fontPressToContinueLine2.loadFromFile( "assets/fonts/sansation.ttf" );
	m_textPressToContinueLine2.setFont( m_fontPressToContinue );
	m_textPressToContinueLine2.setCharacterSize( 15u );
	// m_textPressToContinueLine2.setFillColor( sf::Color::Yellow );
	m_textPressToContinueLine2.setFillColor( sf::Color::White );
	m_textPressToContinueLine2.setString( "\nPress PauseBreak or P to continue" );
	centerOrigin( m_textPressToContinueLine2 );
	m_textPressToContinueLine2.setPosition( ( m_worldView.getSize().x / 2 ), ( ( m_worldView.getSize().y / 2 ) + 50 ) );

	// std::cout << "PauseState Init\t\t\tState Age is: " + std::to_string( getStateAgeAsSeconds() ) + ">>>\n";// TODO delete this debug line
	std::cout << "SETTINGS.inGameOverlay=" << SETTINGS.inGameOverlay << "\t|\tSETTINGS.debugPrintToConsole=" << SETTINGS.debugPrintToConsole << "\t|\tSETTINGS.debugPrintToConsoleFPS=" << SETTINGS.debugPrintToConsoleFPS << "\n\n";// TODO delete this debug line
}

void PauseState::pause()
{
	std::cout << "PauseState Pause" << std::endl;
}

void PauseState::resume()
{
	restartStateClock();
	std::cout << "PauseState Resume\t\t\tState Age is: " + std::to_string( getStateAgeAsSeconds() ) + ">>>\n";	// TODO delete this debug line
}

void PauseState::update()
{
	sf::Time m_elapsedTime = m_clock.restart();
	m_timeSinceLastUpdate += m_elapsedTime;

	while ( m_timeSinceLastUpdate > State::TimePerFrame ) {
		m_timeSinceLastUpdate -= State::TimePerFrame;

		processEvents();

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
		}
	}
}

void PauseState::draw()
{
	// Clear the previous drawing
	m_window.clear();
	m_window.draw( m_bg );
	// debug overlay
	if ( SETTINGS.inGameOverlay ) {
		m_window.draw( m_statisticsText );
	}
	ball->draw( m_window, sf::RenderStates::Default );
	paddleRight->draw( m_window, sf::RenderStates::Default );
	paddleLeft->draw( m_window, sf::RenderStates::Default );

	m_window.	draw(	m_textPressToContinue );
	m_window.	draw(	m_textPressToContinueLine2 );

	m_window.display();
}

void PauseState::processEvents()
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
					case sf::Keyboard::Pause:
					case sf::Keyboard::P:
						m_machine.lastState();
						break;
					case sf::Keyboard::Q:
						m_machine.quit();
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


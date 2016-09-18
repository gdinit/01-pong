/* playstate.cc */

#include <include/playstate.h>

extern Settings				SETTINGS;
// extern Globals			GLOBALS;
extern std::unique_ptr <Globals>	GLOBALS;
extern std::unique_ptr <Paddle>		paddleRight;
extern std::unique_ptr <Paddle>		paddleLeft;
extern std::unique_ptr <Ball>		ball;
// TODO add score here

PlayState::PlayState( StateMachine &machine, sf::RenderWindow &window, bool replace ) : State{ machine, window, replace }
{
	initializeState();
}

void PlayState::initializeState()
{
	restartStateClock();
	m_justResumed = false;

	m_worldView = m_window.getDefaultView();
	m_urgentUpdateNeeded = 10;

	// background
	m_bgTex.loadFromFile( "assets/textures/3playing.png" );
	m_bg.setTexture( m_bgTex, true );

	// debug overlay font
	m_font.loadFromFile( "assets/fonts/sansation.ttf" );
	m_statisticsText.setFont( m_font );
	m_statisticsText.setPosition( 5.f, 5.f );
	m_statisticsText.setCharacterSize( 12u );
	m_statisticsText.setFillColor( sf::Color::White );
	// give me stats in the first frame, but first make up some plausible values
	updateDebugOverlayTextIfEnabled( true );

	// start a new round.
	m_nextThrowTowardsRight = true;
	paddleRight->m_computerControlled = SETTINGS.sideRightIsComputer;
	paddleLeft->m_computerControlled = SETTINGS.sideLeftIsComputer;
	paddleRight->newRound();
	paddleLeft->newRound();
	ball->newRound( m_nextThrowTowardsRight );

	std::cout << "PlayState Init\t\t\tState Age is: " + std::to_string( getStateAgeAsSeconds() ) + ">>>\n";	// TODO delete this debug line
	std::cout << "SETTINGS.inGameOverlay=" << SETTINGS.inGameOverlay <<
		"\t|\tSETTINGS.debugPrintToConsole=" << SETTINGS.debugPrintToConsole <<
		"\t|\tSETTINGS.debugPrintToConsoleFPS=" << SETTINGS.debugPrintToConsoleFPS <<
		"\n\n";		// TODO delete this debug line
}

void PlayState::pause()
{
	std::cout << "PlayState Pause" << std::endl;
}

void PlayState::resume()
{
	restartStateClock();
	m_urgentUpdateNeeded = 10;
	// destroy the queue
	m_justResumed = true;
	updateDebugOverlayTextIfEnabled( true );// give me stats in the first frame, but first make up some plausible values
	std::cout << "PlayState Resume\t\t\tState Age is: " + std::to_string( getStateAgeAsSeconds() ) + ">>>\n";// TODO delete this debug line
}

void PlayState::update()
{
	sf::Time m_elapsedTime = m_clock.restart();
	m_timeSinceLastUpdate += m_elapsedTime;

	// if returning from pause(), let's jump in time to prevent slow catchup process
	if ( m_justResumed ) {
		m_timeSinceLastUpdate = TimePerFrame;
	}

	while ( m_timeSinceLastUpdate > State::TimePerFrame ) {
		m_timeSinceLastUpdate -= State::TimePerFrame;

		processEvents();

		// update paddles right, left and the ball
		paddleRight->update( m_elapsedTime );
		paddleLeft->update( m_elapsedTime );
		ball->update( m_elapsedTime );

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
	m_justResumed = false;
}// exiting update()

void PlayState::draw()
{
	m_window.clear();
	m_window.draw( m_bg );

	// debug overlay
	if ( SETTINGS.inGameOverlay ) {
		m_window.draw( m_statisticsText );
	}

	ball->draw( m_window, sf::RenderStates::Default );
	paddleRight->draw( m_window, sf::RenderStates::Default );
	paddleLeft->draw( m_window, sf::RenderStates::Default );

	// finally, display the updated window
	m_window.display();
}

void PlayState::processEvents()
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
						m_next = StateMachine::build <InGameMenuState> ( m_machine, m_window, false );
						break;
					case sf::Keyboard::Pause:
					case sf::Keyboard::P:
						// TODO add Are you sure? Y/N confirmation here
						m_next = StateMachine::build <PauseState> ( m_machine, m_window, false );
						break;
					case sf::Keyboard::Q:
						// TODO add Are you sure? Y/N confirmation here
						m_machine.quit();
						break;
					case sf::Keyboard::M:
						// TODO add Are you sure? Y/N confirmation here
						m_next = StateMachine::build <MainMenuState> ( m_machine, m_window, true );
						break;
					case sf::Keyboard::Up:
						GLOBALS->moveUpRequestActive = true;
						break;
					case sf::Keyboard::Down:
						GLOBALS->moveDownRequestActive = true;
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
			case sf::Event::KeyReleased:
				switch ( evt.key.code ) {
					case sf::Keyboard::Up:
						GLOBALS->moveUpRequestActive = false;
						break;
					case sf::Keyboard::Down:
						GLOBALS->moveDownRequestActive = false;
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


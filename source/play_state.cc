/* play_state.cc */

#include "play_state.h"

extern std::unique_ptr <Settings>	SETTINGS;
extern std::unique_ptr <Globals>	GLOBALS;
extern std::unique_ptr <Paddle>		paddleRight;
extern std::unique_ptr <Paddle>		paddleLeft;
extern std::unique_ptr <Ball>		ball;
extern std::unique_ptr <Scoreboard>	scoreboard;
extern std::unique_ptr <Brick>		brick;

PlayState::PlayState( StateMachine &machine, sf::RenderWindow &window, bool
	replace )
	: State{ machine, window, replace }
{
	initializeState();
}

void PlayState::initializeState()
{
	restartStateClock();
	m_justResumed = false;
	m_worldView = m_window.getDefaultView();
	m_urgentUpdateNeeded = 10;

	// debug overlay font
	m_font.loadFromFile( "assets/fonts/sansation.ttf" );
	m_statisticsText.setFont( m_font );
	m_statisticsText.setPosition( 5.f, 5.f );
	m_statisticsText.setCharacterSize( 12u );
	m_statisticsText.setFillColor( sf::Color::White );
	updateDebugOverlayTextIfEnabled( true );

	// start a new round.
	m_nextThrowTowardsRight = true;
	paddleRight->m_computerControlled = SETTINGS->sideRightIsComputer;
	paddleLeft->m_computerControlled = SETTINGS->sideLeftIsComputer;
	paddleRight->newRound();
	paddleLeft->newRound();
	GLOBALS->scoreLeftSide = 0;
	GLOBALS->scoreRightSide = 0;
	ball->newRound( m_nextThrowTowardsRight );
	scoreboard->centrePosition();
}

void PlayState::pause()
{
}

void PlayState::resume()
{
	restartStateClock();
	m_urgentUpdateNeeded = 10;
	// destroy the queue
	m_justResumed = true;
	// give me stats in the first frame, but first make up some plausible
	// values
	updateDebugOverlayTextIfEnabled( true );
}

void PlayState::update()
{
	sf::Time m_elapsedTime = m_clock.restart();
	m_timeSinceLastUpdate += m_elapsedTime;

	// if returning from pause(), let's jump in time to prevent slow catchup
	// process
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
		scoreboard->update( m_elapsedTime );

		// update statistics for the debug overlay
		m_statisticsUpdateTime += m_elapsedTime;
		m_statisticsNumFrames += 1;
		// update statsText only once a second
		if ( m_urgentUpdateNeeded > 0 ) {
			// update now!
			--m_urgentUpdateNeeded;
			updateDebugOverlayTextIfEnabled();
			printConsoleDebugIfEnabled();
			m_urgentUpdateNeeded = false;
		}
		if ( m_statisticsUpdateTime >= sf::seconds( 1.0f ) ) {
			if ( m_statisticsNumFrames <= 1 ) {
				break;	// if we're playing catchup, don't
					// bother with debugOverlayText
			}

			recordObservedFPS();
			dynamicallyAdjustFPSLimit();

			updateDebugOverlayTextIfEnabled();
			printConsoleDebugIfEnabled();

			m_statisticsUpdateTime -= sf::seconds( 1.0f );
			m_statisticsNumFrames = 0;
		}
	}
	m_justResumed = false;
}

void PlayState::draw()
{
	m_window.clear();
	m_window.draw( m_bg );
	if ( SETTINGS->inGameOverlay ) {
		m_window.draw( m_statisticsText );
	}
	brick->draw( m_window, sf::RenderStates::Default );
	ball->draw( m_window, sf::RenderStates::Default );
	paddleRight->draw( m_window, sf::RenderStates::Default );
	paddleLeft->draw( m_window, sf::RenderStates::Default );
	scoreboard->draw( m_window, sf::RenderStates::Default );
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
						// InGameMenuState is commented
						// out for the time being and
						// replaced with PauseState
						// m_next = StateMachine::build
						// <InGameMenuState> (
						// m_machine, m_window, false );
						m_next =
							StateMachine::	build <
								PauseState> (
								m_machine
								, m_window
								, false );
						break;
					case sf::Keyboard::Pause:
					case sf::Keyboard::P:
						m_next =
							StateMachine::	build <
								PauseState> (
								m_machine
								, m_window
								, false );
						break;
					case sf::Keyboard::Q:
						m_machine.quit();
						break;
					case sf::Keyboard::M:
						m_next =
							StateMachine::build <
								MainMenuState> (
								m_machine
								, m_window
								, true );
						break;
					case sf::Keyboard::Up:
					case sf::Keyboard::W:
						GLOBALS->moveUpRequestActive =
							true;
						break;
					case sf::Keyboard::Down:
					case sf::Keyboard::S:
						GLOBALS->moveDownRequestActive =
							true;
						break;
					case sf::Keyboard::F2:
						this->toggleDebugShowOverlay();
						break;
					case sf::Keyboard::F3:
						this->toggleDebugConsoleOutput();
						break;
					case sf::Keyboard::F4:
						this->
						toggleDebugDynFPSConsoleOutput();
						break;
					default:
						break;
				}
				break;
			case sf::Event::KeyReleased:
				switch ( evt.key.code ) {
					case sf::Keyboard::Up:
					case sf::Keyboard::W:
						GLOBALS->moveUpRequestActive =
							false;
						break;
					case sf::Keyboard::Down:
					case sf::Keyboard::S:
						GLOBALS->moveDownRequestActive =
							false;
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


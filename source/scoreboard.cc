/* scoreboard.cc */

#include <include/scoreboard.h>

extern std::unique_ptr <Settings>	SETTINGS;
extern std::unique_ptr <Globals>	GLOBALS;
extern std::unique_ptr <Ball>		ball;

Scoreboard::Scoreboard()
{
	// ctor
	m_scoreFont.loadFromFile( "assets/fonts/sansation.ttf" );
	m_scoreText.setFont( m_scoreFont );
	m_scoreText.setPosition( -100, -100 );
	m_scoreText.setCharacterSize( 60u );
	m_scoreText.setFillColor( sf::Color::White );
}

Scoreboard::~Scoreboard()
{
}

void Scoreboard::incrementLeft()
{
	// NOT IN USE
	// ++m_scoreLeftSide;
}

void Scoreboard::incrementRight()
{
	// NOT IN USE
	// ++m_scoreRightSide;
}

void Scoreboard::centrePosition()
{
	m_scoreText.setPosition( ( SETTINGS->currentScreenSizeWidth / 2 ), +60.f );
}

void Scoreboard::update( sf::Time timeSinceLastUpdate )
{
	m_scoreText.setString( std::to_string( GLOBALS->scoreLeftSide ) + "          " + std::to_string( GLOBALS->scoreRightSide ) );
	centerOrigin( m_scoreText );
}

void Scoreboard::draw( sf::RenderTarget &target, sf::RenderStates states ) const {
	target.draw( m_scoreText );
}

/* EOF */


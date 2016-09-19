/* ball.cc */

#include <include/ball.h>

extern std::unique_ptr <Settings>	SETTINGS;
extern std::unique_ptr <Globals>	GLOBALS;
extern std::unique_ptr <Ball>		ball;
extern std::unique_ptr <Paddle>		paddleRight;
extern std::unique_ptr <Paddle>		paddleLeft;

Ball::Ball()
{
	// ctor
	m_shape.setPosition( CONFIG_BALL_SPAWN_POS, CONFIG_BALL_SPAWN_POS );
	m_shape.setOrigin( CONFIG_BALL_WIDTH / 2.f, CONFIG_BALL_HEIGHT / 2.f );
	m_shape.setSize( { CONFIG_BALL_WIDTH, CONFIG_BALL_HEIGHT } );

	// each hit will accelerate the ball this much
	m_cfg_acceleration_val = CONFIG_BALL_ONHIT_ACCELERATION;

	// no hits so far, thus the acceleration is zero
	m_acceleration.x = 0.f;
	m_acceleration.y = 0.f;

	// no hits so far, thus the velocity is zero
	m_velocity.x = 0.f;
	m_velocity.y = 0.f;
}

Ball::~Ball()
{
}

void Ball::newRound( bool throwTowardsRightSide )
{
	// TODO: generate random throw angle towards last round's loser (limited randomness, within parameters)
	// TODO: generate random speed   (limited randomness, within parameters)

	// TODO delete this test hardcode <-- ALWAYS THROW LEFT
	throwTowardsRightSide = false;

	sf::Vector2f	centreOfScreen;
	centreOfScreen.x = SETTINGS->currentScreenSizeWidth / 2;
	centreOfScreen.y = SETTINGS->currentScreenSizeHeight / 2;
	this->m_shape.setPosition( centreOfScreen );

	sf::Vector2f	ballPos = centreOfScreen;

	sf::Vector2f	targetPos;
	if ( throwTowardsRightSide ) {
		targetPos.x = paddleRight->getX();
		targetPos.y = paddleRight->getY();
	} else {
		targetPos.x = paddleLeft->getX();
		targetPos.y = paddleLeft->getY();
	}

	sf::Vector2f ballNewVel;
	// ballNewVel.x = ( targetPos.x - ballPos.x );
	// ballNewVel.y = ( targetPos.y - ballPos.y );
	ballNewVel.x = ( targetPos.x - ballPos.x ) / 1000;
	ballNewVel.y = ( targetPos.y - ballPos.y ) / 1000;

	////////////////////////////////////////////////////////////
	// speed test: multiply speed by 3
	//
	// ballNewVel.x *= 3;
	// ballNewVel.y *= 3;
	////////////////////////////////////////////////////////////
	// throw direction tests
	//
	// throw towards:	top left
	// ballNewVel.x = -1;
	// ballNewVel.y = -0.7216;
	//
	// throw towards:	bottom left
	// ballNewVel.x = -1;
	// ballNewVel.y = 0.7216;
	//
	// throw towards:	top right
	// ballNewVel.x = 1;
	// ballNewVel.y = -0.7216;

	// throw towards:	bottom right
	// ballNewVel.x = 1;
	// ballNewVel.y = 0.7216;
	////////////////////////////////////////////////////////////

	ballNewVel.x = 1;
	ballNewVel.y = 0.7216;

	std::cout << "AFTER DIVISION ballNewVel is: " << std::to_string( ballNewVel.x ) << "," << std::to_string( ballNewVel.y ) << "\n";// TODO delete this debug line
	std::cout << "ballPos is: " << std::to_string( ballPos.x ) << "," << std::to_string( ballPos.y ) << "\n";// TODO delete this debug line
	std::cout << "throwTowardsRightSide is: " << throwTowardsRightSide << "\ttargetPos is: " << std::to_string( targetPos.x ) << "," << std::to_string( targetPos.y ) << "\n";	// TODO delete this debug line
	std::cout << "ballNewVel is: " << std::to_string( ballNewVel.x ) << "," << std::to_string( ballNewVel.y ) << "\n";	// TODO delete this debug line

	// TODO generate slightly randomized ball direction towards throwTarget, within parameters = max variance is 45 degrees to either way (up/down)
	/*
	        to find the length:

	        |V| = sqrt(4 2ndpower+3 2ndpower) = sqrt(25) = 5
	        int ballNewVelx2nd = ballNewVel.x * ballNewVel.x;
	        int ballNewVely2nd = ballNewVel.y * ballNewVel.y;
	        int ballNewVelxy2ndsum = ballNewVelx2nd + ballNewVely2nd;
	        cout << ballNewVelxy2ndsum << endl;
	*/
	float	ballNewVelMagnitudeSquared = magnitudeSquared( ballNewVel.x, ballNewVel.y );
	float	ballNewVelMagnitude = magnitude( ballNewVel.x, ballNewVel.y );
	std::cout << "***** ballNewVelMagnitudeSquared: " << ballNewVelMagnitudeSquared << std::endl;
	std::cout << "***** ballNewVelMagnitude: " << ballNewVelMagnitude << std::endl;
	// int randomVal = 45;
	// ballNewVel.y += randomVal;
	this->m_velocity = ballNewVel;
}

void Ball::update( sf::Time timeSinceLastUpdate )
{
	std::cout << "(Pre-Update) ballPos is: " << std::to_string( this->getX() ) << "," << std::to_string( this->getY() ) << "\n";	// TODO delete this debug line

	// BOUNCE BACK IF NECESSARY
	if ( this->getTop() <= SETTINGS->playAreaTopLine ) {
		this->m_velocity = -( this->m_velocity );
	}
	if ( this->getBottom() >= SETTINGS->playAreaBottomLine ) {
		this->m_velocity = -( this->m_velocity );
	}

	sf::Vector2f moveDistance;
	moveDistance.x = ( this->m_velocity.x * SETTINGS->ballSlower ) * timeSinceLastUpdate.asMilliseconds();
	moveDistance.y = ( this->m_velocity.y * SETTINGS->ballSlower ) * timeSinceLastUpdate.asMilliseconds();
	this->m_shape.move( moveDistance );
}

void Ball::draw( sf::RenderTarget &target, sf::RenderStates states ) const {
	target.draw( this->m_shape );
}

float Ball::getX() const noexcept
{
	return m_shape.getPosition().x;
}

float Ball::getY() const noexcept
{
	return m_shape.getPosition().y;
}

float Ball::getTop() const noexcept
{
	return getY() - m_shape.getSize().y / 2.f;
}

float Ball::getBottom() const noexcept
{
	return getY() + m_shape.getSize().y / 2.f;
}

/* EOF */


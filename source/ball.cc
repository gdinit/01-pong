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
	throwTowardsRightSide = false;	// TODO delete this line // test hardcode = ALWAYS THROW LEFT

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

	/*
	STEPS
	        obtain ball pos
	        obtain target pos
	        calculate the two vector angle points:
	                a) MAX: laser from ballCurPos to ballTargetPos (highest point to throw the ball towards). -1,+0.7216 is top left, in my test
	                b) MIN: laser from ballCurPos to ballTargetPos (lowest point to throw the ball towards). -1,-0.7216 is bottom left, in my test
	        since X is constant, do nothing about it
	        since Y is variable, generate a random float between yMin & yMax values
	        set the ballNewVel accordingly to throw the ball
	        generate a random value within ballNewSpeedMin/ballNewSpeedMax values, pick a random value, asssign it to ballNewSpeed
	        modify the ballNewVel to match the ballNewSpeed
	*/
	sf::Vector2f	ballNewVel;
	float		throwTargetX = SETTINGS->sideRightSpawnX;
	float		throwTargetY = 0, randomlyChosenRowMin = 0, randomlyChosenRowMax = 0, randomlyChosenRow = 0;
	randomlyChosenRowMin = SETTINGS->playAreaTopLine;
	randomlyChosenRowMax = SETTINGS->playAreaBottomLine;
	randomlyChosenRow = 45;	// TEST WITH HARD CODED VALUES // TODO: add actual random float generation here between randomlyChosenRowMin & randomlyChosenRowMax
	throwTargetY = randomlyChosenRow;

	ballNewVel.x = throwTargetX - ballPos.x;
	ballNewVel.y = throwTargetY - ballPos.y;

	// TODO get the length (magnitude) of vector here
	float		ballNewVelLength = magnitude( ballNewVel.x, ballNewVel.y );

	sf::Vector2f	ballNewVelNormalized = normalize( ballNewVel );

	float		ballNewVelNormalizedLength = magnitude( ballNewVelNormalized.x, ballNewVelNormalized.y );

	// TODO normalize the velocity vector here

	// TODO generate +/-20% newSpeed here

	// TODO multiply normalized vector with newSpeed here

	std::cout << "////////////////////////////////////////////////////////////\n";
	std::cout << "ballPos: " << std::to_string( ballPos.x ) << "," << std::to_string( ballPos.y ) << "\n";	// TODO delete this debug line
	std::cout << "throwTowardsRightSide: " << throwTowardsRightSide << "\n";// TODO delete this debug line
	std::cout << "targetPos: " << std::to_string( targetPos.x ) << "," << std::to_string( targetPos.y ) << "\n";	// TODO delete this debug line
	std::cout << "throwTarget: " << std::to_string( throwTargetX ) << " | throwTargetY: " << std::to_string( throwTargetY ) << "\n";// TODO delete this debug line
	std::cout << "ballNewVel: " << std::to_string( ballNewVel.x ) << "," << std::to_string( ballNewVel.y ) << "\n";	// TODO delete this debug line
	std::cout << "ballNewVelLength: " << ballNewVelLength << "\n";	// TODO delete this debug line
	std::cout << "ballNewVelNormalized: " << std::to_string( ballNewVelNormalized.x ) << "," << std::to_string( ballNewVelNormalized.y ) << "\n";	// TODO delete this debug line
	std::cout << "ballNewVelNormalizedLength: " << ballNewVelNormalizedLength << "\n";	// TODO delete this debug line

	// TODO multiply normalized vector with newSpeed here
	ballNewVelNormalized.x = ballNewVelNormalized.x * 0.20;
	ballNewVelNormalized.y = ballNewVelNormalized.y * 0.20;
	ballNewVelNormalizedLength = magnitude( ballNewVelNormalized.x, ballNewVelNormalized.y );
	std::cout << "ballNewVelNormalized new1: " << std::to_string( ballNewVelNormalized.x ) << "," << std::to_string( ballNewVelNormalized.y ) << "\n";	// TODO delete this debug line
	std::cout << "ballNewVelNormalizedLength new1: " << ballNewVelNormalizedLength << "\n";	// TODO delete this debug line

	// TODO: generate random throw angle towards last round's loser (limited randomness, within parameters)
	// TODO: generate random speed variation +/-20% of standard speed
	this->m_velocity = ballNewVelNormalized;
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
	/*
	old code

	moveDistance.x = ( this->m_velocity.x * SETTINGS->ballSlower ) * timeSinceLastUpdate.asMilliseconds();
	moveDistance.y = ( this->m_velocity.y * SETTINGS->ballSlower ) * timeSinceLastUpdate.asMilliseconds();

	*/

	////////////////////////////////////////////////////////////////////////////////
	// NEW MOVEMENT CODE - begin

	/*
	The velocity is a combination of a normalised sf::Vector2f member variable which represents the current direction of the ball
	and a constant value, speed.

	Every update the ball is moved by m_velocity * m_speed * dt, where dt is the time elapsed since the last update.
	*/

	// NEW CODE MOVEMENT - end
	moveDistance.x = ( this->m_velocity.x * SETTINGS->ballSpeed ) * timeSinceLastUpdate.asMilliseconds();
	moveDistance.y = ( this->m_velocity.y * SETTINGS->ballSpeed ) * timeSinceLastUpdate.asMilliseconds();
	////////////////////////////////////////////////////////////////////////////////

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


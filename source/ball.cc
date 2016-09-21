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
	throwTowardsRightSide = true;	// TODO delete this line // test hardcode = ALWAYS THROW LEFT

	// put the ball to screen centre
	sf::Vector2f				centreOfScreen { ( centreOfScreen.x = SETTINGS->currentScreenSizeWidth / 2 ), ( centreOfScreen.y = SETTINGS->currentScreenSizeHeight / 2 ) };
	this->m_shape.setPosition( centreOfScreen );

	// calculate new ball velocity
	sf::Vector2f				ballNewVel;
	float					throwTargetX = 0;
	if ( throwTowardsRightSide ) {
		throwTargetX = SETTINGS->sideRightSpawnX;
	} else {
		throwTargetX = SETTINGS->sideLeftSpawnX;
	}
	float					throwTargetY = 0;

	// randomize ball direction
	std::mt19937				mt1;
	auto					seed1 = std::chrono::high_resolution_clock::now().time_since_epoch().count();
	mt1.seed( ( unsigned long )seed1 );
	std::uniform_real_distribution <>	dist1( SETTINGS->playAreaTopLine, SETTINGS->playAreaBottomLine );
	throwTargetY = dist1( mt1 );

	// calculate new velocity
	sf::Vector2f				ballPos = centreOfScreen;
	ballNewVel.x = throwTargetX - ballPos.x;
	ballNewVel.y = throwTargetY - ballPos.y;

	// normalize the velocity vector & assign it to the object
	sf::Vector2f				ballNewVelNormalized = normalize( ballNewVel );
	this->m_velocity = ballNewVelNormalized;
}

void Ball::update( sf::Time timeSinceLastUpdate )
{
	// std::cout << "(Pre-Update) ballPos is: " << std::to_string( this->getX() ) << "," << std::to_string( this->getY() ) << "\n";	// TODO delete this debug line

	// bounce back if necessary
	if ( this->getTop() <= SETTINGS->playAreaTopLine ) {
		this->m_velocity = -( this->m_velocity );
	}
	if ( this->getBottom() >= SETTINGS->playAreaBottomLine ) {
		this->m_velocity = -( this->m_velocity );
	}

	// calculate
	sf::Vector2f moveDistance;
	moveDistance.x = ( this->m_velocity.x * SETTINGS->ballSpeed ) * timeSinceLastUpdate.asMilliseconds();
	moveDistance.y = ( this->m_velocity.y * SETTINGS->ballSpeed ) * timeSinceLastUpdate.asMilliseconds();

	// action
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


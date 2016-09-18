/* ball.cc */

#include <include/ball.h>

extern std::unique_ptr <Settings>	SETTINGS;
extern std::unique_ptr <Globals>	GLOBALS;
extern std::unique_ptr <Ball>		ball;

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
	sf::Vector2f	centreOfScreen;
	centreOfScreen.x = SETTINGS->currentScreenSizeWidth / 2;
	centreOfScreen.y = SETTINGS->currentScreenSizeHeight / 2;

	this->m_shape.setPosition( centreOfScreen );

	// give the initial test push // TODO replace me with random direction & speed generator
	sf::Vector2f	vel;
	vel.x = 1;
	vel.y = -1;
	this->m_velocity = vel;

	// TODO
	// move ball to centre of screen //shape.setPosition( mX, mY );
	// generate random direction towards throwTarget (within parameters)
	// generate random speed  (within parameters)
	// (random-ish speed towards the throwTarget
}

void Ball::update( sf::Time timeSinceLastUpdate )
{
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


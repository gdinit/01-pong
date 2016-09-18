/* ball.cc */

#include <include/ball.h>

extern Settings SETTINGS;

Ball::Ball()
{
	// ctor
	m_shape.setPosition( CONFIG_BALL_SPAWN_POS, CONFIG_BALL_SPAWN_POS );
	m_shape.setOrigin( CONFIG_BALL_WIDTH / 2.f, CONFIG_BALL_HEIGHT / 2.f );
	m_shape.setSize( { CONFIG_BALL_WIDTH, CONFIG_BALL_HEIGHT } );

	// each hit will accelerate the ball this much
	m_cfg_acceleration_val = CONFIG_BALL_ONHIT_ACCELERATION;

	// each frame will slow down the ball this much
	m_friction.x = CONFIG_BALL_FRICTION;
	m_friction.y = CONFIG_BALL_FRICTION;

	// no hits so far, thus the acceleration is zero
	m_acceleration.x = 0.f;
	m_acceleration.y = 0.f;

	// no hits so far, thus the velocity is zero
	m_velocity.x = 0.f;
	m_velocity.y = 0.f;

	// TODO
	// do a newRound() here

	// report for debugging // TODO remove this debug section
	sf::Vector2f v;
	v.x = this->m_shape.getPosition().x;
	v.y = this->m_shape.getPosition().y;
	std::cerr << "Ball [" << this << "] constructed at coordinates" << std::to_string( v.x ) << "," << std::to_string( v.y ) << "\n\n";
}

Ball::~Ball()
{
	// dtor
	std::cerr << "Ball [" << this << "] destructed\n";
}

/*! Position ball at center and throw to start a new round.
 * \param val Target side to throw the ball towards

    On the very first round, throw towards the right side.
    In subsequent rounds, throw towards the previous round's losing side.
    Both the speed and direction has some randomness to it.
*/
void Ball::newRound( bool throwTowardsRightSide )
{
	sf::Vector2f centreOfScreen;
	centreOfScreen.x = SETTINGS.currentScreenSizeWidth / 2;
	centreOfScreen.y = SETTINGS.currentScreenSizeHeight / 2;

	// TODO
	// add newRound code here
	// PSEUDO CODE
	// 1. teleport to centre of screen

	this->m_shape.setPosition( centreOfScreen );
	std::cout << "Ball::newRound triggered! received value throwTowardsRightSide=" << throwTowardsRightSide << "\n";

	// give the initial test push // TODO replace me with random direction & speed generator
	sf::Vector2f vel;
	vel.x = 1;
	vel.y = -1;
	this->m_velocity = vel;

	/*
	std::cout << "Ball::newRound received values --> x,y=" << std::to_string( middleOfScreen.x ) << "," << std::to_string( middleOfScreen.y ) << " | throwTowardsRightSide=" << throwTowardsRightSide << std::endl;
	std::cout << "Ball::newRound pre values --> x,y=" << std::to_string( this->getPosition().x ) << "," << std::to_string( this->getPosition().y ) << "\n";
	this->setPosition( middleOfScreen );
	std::cout << "Ball::newRound post values --> x,y=" << std::to_string( this->getPosition().x ) << "," << std::to_string( this->getPosition().y ) << "\n";
	*/
	// move ball to centre of screen //shape.setPosition( mX, mY );
	// generate random direction towards throwTarget (within parameters)
	// generate random speed  (within parameters)
	// (random-ish speed towards the throwTarget
}

// void Ball::update( sf::Time timeSinceLastUpdate )
// {
// std::cout << "\tBall updating...\n";	// TODO delete this debug line
// }
/*
SETTINGS.playAreaTopLine = CONFIG_PLAYAREA_INDENT_TOP;
SETTINGS.playAreaBottomLine = CONFIG_PLAYAREA_INDENT_BOTTOM;
*/
/*! Update the ball
* \param val Delta time
*/
void Ball::update( sf::Time timeSinceLastUpdate )
{
	// BOUNCE IF NECESSARY
	// if reached top of the playable area, bounce back
	if ( this->getTop() <= SETTINGS.playAreaTopLine ) {
		this->m_velocity = -( this->m_velocity );
		// std::cout << "Ball bounced back from top.\n";	// TODO delete this debug line
	}
	// if reached bottom of the playable area, bounce back
	if ( this->getBottom() >= SETTINGS.playAreaBottomLine ) {
		this->m_velocity = -( this->m_velocity );
		// std::cout << "Ball bounced back from bottom.\n";// TODO delete this debug line
	}

	// TODO ADD ACCELERATION TO VELOCITY & ZERO OUT ACCELERATION

	// MOVE THE MAIN BALL OBJECT
	sf::Vector2f moveDistance;
	moveDistance.x = ( this->m_velocity.x * SETTINGS.ballSlower ) * timeSinceLastUpdate.asMilliseconds();
	moveDistance.y = ( this->m_velocity.y * SETTINGS.ballSlower ) * timeSinceLastUpdate.asMilliseconds();
	this->m_shape.move( moveDistance );
	// std::cout << "BallCurPos x.y is: " << this->m_shape.getPosition().x << "," << this->m_shape.getPosition().y << "\tBallCurVel is x.y: " << m_velocity.x << "," << m_velocity.y << "\ttimeSinceLastUpdate.asMilliseconds() is: " << std::to_string( timeSinceLastUpdate.asMilliseconds() ) << "\tSETTINGS.ballSlower is: " << SETTINGS.ballSlower << "\n";// TODO delete this debug line
}

/** Draw the shape on screen.
 * \param tar Render target
 * \param sta States
 */
void Ball::draw( sf::RenderTarget &target, sf::RenderStates states ) const {
	target.draw( this->m_shape );
}

/** Move the shape on screen in -Y axis.
 * \param val Delta time
 */
// void Ball::moveUp( sf::Time val ) {
// TODO
// add moveUp stuff here
// }

/** Move the shape on screen in +Y axis.
 * \param val Delta time
 */
// void Ball::moveDown( sf::Time val ) {
// TODO
// add moveDown stuff here
// }

/*
void Ball::moveLittle() {
        this->m_shape.move( 5, -15 );
        std::cout << "ball is at: " << this->m_shape.getPosition().x << "\n";
}
*/

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


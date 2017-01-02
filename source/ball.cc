/* ball.cc */

#include <include/ball.h>

extern std::unique_ptr <Settings>	SETTINGS;
extern std::unique_ptr <Globals>	GLOBALS;
extern std::unique_ptr <Ball>		ball;
extern std::unique_ptr <Paddle>		paddleRight;
extern std::unique_ptr <Paddle>		paddleLeft;
extern std::unique_ptr <Scoreboard>	scoreboard;

Ball::Ball()
{
	// ctor
	m_texture.loadFromFile( "assets/textures/white.png" );

	// Create a sprite
	m_sprite.setTexture( m_texture );
	m_sprite.setTextureRect( sf::IntRect( CONFIG_BALL_SPAWN_POS, CONFIG_BALL_SPAWN_POS, CONFIG_BALL_WIDTH, CONFIG_BALL_HEIGHT ) );
	m_sprite.setOrigin( CONFIG_BALL_WIDTH / 2.f, CONFIG_BALL_HEIGHT / 2.f );

	// no hits so far, thus the velocity is zero
	m_velocity.x = 0.f;
	m_velocity.y = 0.f;

	if ( !m_sbColPaddle.loadFromFile( "assets/sounds/collision1.wav" ) ) {
	}
	m_sColPaddle.setBuffer( m_sbColPaddle );

	if ( !m_sbColWall.loadFromFile( "assets/sounds/collision2.wav" ) ) {
	}
	m_sColWall.setBuffer( m_sbColWall );

	if ( !m_sbColGoal.loadFromFile( "assets/sounds/goal1.wav" ) ) {
	}
	m_sColGoal.setBuffer( m_sbColGoal );
}

Ball::~Ball() {}

void Ball::newRound( bool throwTowardsRightSide )
{
	// put the ball to screen centre
	sf::Vector2f				centreOfScreen { ( centreOfScreen.x = SETTINGS->currentScreenSizeWidth / 2 ), ( centreOfScreen.y = SETTINGS->currentScreenSizeHeight / 2 ) };
	this->m_sprite.setPosition( centreOfScreen );

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

void Ball::collisionDetectRespond( void ) noexcept
{
	// DETECT PADDLE COLLISION
	bool		reverseNeeded = false;
	sf::FloatRect	boundingBoxBall = m_sprite.getGlobalBounds();
	sf::FloatRect	boundingBoxPaddleRight = paddleRight->m_sprite.getGlobalBounds();
	sf::FloatRect	boundingBoxPaddleLeft = paddleLeft->m_sprite.getGlobalBounds();
	if ( boundingBoxBall.intersects( boundingBoxPaddleRight ) ) {
		reverseNeeded = true;
	} else if ( boundingBoxBall.intersects( boundingBoxPaddleLeft ) ) {
		reverseNeeded = true;
	} else {
	}
	if ( reverseNeeded ) {
		m_sColPaddle.play();

		// reverse ball direction
		this->m_velocity = -( this->m_velocity );
	}

	// DETECT GOAL COLLISION
	if ( this->getRight() >= CONFIG_GOAL_LINE_RIGHT ) {
		// Play goal sound effect
		m_sColGoal.play();
		++GLOBALS->scoreLeftSide;
		ball->newRound( true );
	}

	if ( this->getLeft() <= CONFIG_PLAY_AREA_OUTSIDE_LEFT ) {
		// Play goal sound effect
		m_sColGoal.play();
		++GLOBALS->scoreRightSide;
		ball->newRound( false );
	}
}

void Ball::update( sf::Time timeSinceLastUpdate )
{
	// =========== bounceback from top & bottom
	if ( this->getTop() <= SETTINGS->playAreaTopLine || this->getBottom() >= SETTINGS->playAreaBottomLine ) {
		this->m_velocity.y = -( this->m_velocity.y );
		m_sColWall.play();
	}
	// calculate
	sf::Vector2f moveDistance;
	moveDistance.x = ( this->m_velocity.x * SETTINGS->ballSpeed ) * timeSinceLastUpdate.asMilliseconds();
	moveDistance.y = ( this->m_velocity.y * SETTINGS->ballSpeed ) * timeSinceLastUpdate.asMilliseconds();
	// action
	this->m_sprite.move( moveDistance );

	this->collisionDetectRespond();
}

void Ball::draw( sf::RenderTarget &target, sf::RenderStates states ) const { target.draw( this->m_sprite ); }

float Ball::getLeft()    const noexcept { return getX() - ( CONFIG_BALL_WIDTH / 2.f ); }

float Ball::getRight()   const noexcept { return getX() + ( CONFIG_BALL_WIDTH / 2.f ); }

float Ball::getX() const noexcept { return m_sprite.getPosition().x; }

float Ball::getY() const noexcept { return m_sprite.getPosition().y; }

float Ball::getTop() const noexcept { return getY() - ( CONFIG_BALL_HEIGHT / 2.f ); }

float Ball::getBottom() const noexcept { return getY() + ( CONFIG_BALL_HEIGHT / 2.f ); }

/* EOF */


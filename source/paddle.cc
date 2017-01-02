/* paddle.cc */

#include <include/paddle.h>

extern std::unique_ptr <Settings>	SETTINGS;
extern std::unique_ptr <Globals>	GLOBALS;
extern std::unique_ptr <Ball>		ball;

Paddle::Paddle( bool thisIsRightPaddle )
{
	// ctor
	m_texture.loadFromFile( "assets/textures/white.png" );

	// Create a sprite
	if ( thisIsRightPaddle ) {
		m_sprite.setTexture( m_texture );
		m_sprite.setTextureRect( sf::IntRect( -100, -100, CONFIG_PADDLE_WIDTH, CONFIG_PADDLE_HEIGHT ) );
		this->m_thisIsRightPaddle = true;
	} else {
		m_sprite.setTexture( m_texture );
		m_sprite.setTextureRect( sf::IntRect( -200, -200, CONFIG_PADDLE_WIDTH, CONFIG_PADDLE_HEIGHT ) );
		this->m_thisIsRightPaddle = false;
	}
	this->m_sprite.setOrigin( CONFIG_PADDLE_WIDTH / 2.f, CONFIG_PADDLE_HEIGHT / 2.f );
}

Paddle::~Paddle() {}

void Paddle::newRound()
{
	// reset paddle positions
	if ( this->m_thisIsRightPaddle ) {
		this->m_sprite.setPosition( ( SETTINGS->currentScreenSizeWidth - SETTINGS->paddleIndent ), SETTINGS->currentScreenSizeHeight / 2 );
	} else {
		this->m_sprite.setPosition( SETTINGS->paddleIndent, SETTINGS->currentScreenSizeHeight / 2 );
	}
}

void Paddle::update( sf::Time timeSinceLastUpdate )
{
	if ( m_thisIsRightPaddle ) {
	} else {
	}

	if ( this->m_computerControlled ) {
		// do Computer-Player stuff here
		float	myTop = this->getTop();
		float	myBottom = this->getBottom();
		float	ballY = ball->getY();
		float	myY = this->getY();

		// do Computer-Player stuff here
		// if ( ( ballY < myY ) && ( myTop > SETTINGS->playAreaTopLine ) ) {
		if ( ( ballY < myY ) && ( myY - ballY > CONFIG_PADDLE_MIN_DIFFERENCE ) && ( myTop > SETTINGS->playAreaTopLine ) ) {
			sf::Vector2f moveDistance( ( 0.f ), ( moveDistance.y = CONFIG_PADDLE_MOVEMENT_NEG_STEP ) );
			this->m_sprite.move( moveDistance );
		} else if ( ( ballY > myY ) && ( ballY - myY > CONFIG_PADDLE_MIN_DIFFERENCE ) && ( myBottom < SETTINGS->playAreaBottomLine ) ) {
			sf::Vector2f moveDistance( ( 0.f ), ( moveDistance.y = CONFIG_PADDLE_MOVEMENT_POS_STEP ) );
			this->m_sprite.move( moveDistance );
		}
	} else {
		// do Human-Player stuff here
		processHumanMovement();
	}
}

void Paddle::draw( sf::RenderTarget &target, sf::RenderStates states ) const { target.draw( m_sprite ); }

/*
float Paddle::getLeft()    const noexcept { return getX() - m_sprite.getSize().x / 2.f; }
float Paddle::getRight()   const noexcept { return getX() + m_sprite.getSize().x / 2.f; }
*/
float Paddle::getX() const noexcept { return m_sprite.getPosition().x; }

float Paddle::getY() const noexcept { return m_sprite.getPosition().y; }

float Paddle::getTop() const noexcept { return getY() - CONFIG_PADDLE_HEIGHT / 2.f; }

float Paddle::getBottom() const noexcept { return getY() + CONFIG_PADDLE_HEIGHT / 2.f; }

void Paddle::processHumanMovement()
{
	if ( GLOBALS->moveUpRequestActive ) {
		float myTop = this->getTop();
		if ( ( myTop - CONFIG_PADDLE_MOVEMENT_POS_STEP ) > SETTINGS->playAreaTopLine ) {
			sf::Vector2f moveDistance( ( 0.f ), ( CONFIG_PADDLE_MOVEMENT_NEG_STEP ) );
			this->m_sprite.move( moveDistance );
		}
	}
	if ( GLOBALS->moveDownRequestActive ) {
		float myBottom = this->getBottom();
		if ( ( myBottom + CONFIG_PADDLE_MOVEMENT_POS_STEP ) < SETTINGS->playAreaBottomLine ) {
			sf::Vector2f moveDistance( ( 0.f ), ( CONFIG_PADDLE_MOVEMENT_POS_STEP ) );
			this->m_sprite.move( moveDistance );
		}
	}
}

/* EOF */


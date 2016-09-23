/* paddle.cc */

#include <include/paddle.h>

extern std::unique_ptr <Settings>	SETTINGS;
extern std::unique_ptr <Globals>	GLOBALS;
extern std::unique_ptr <Ball>		ball;

Paddle::Paddle( bool thisIsRightPaddle )
{
	// ctor

	if ( thisIsRightPaddle ) {
		this->m_shape.setPosition( -100, -100 );
		this->m_thisIsRightPaddle = true;
	} else {
		this->m_shape.setPosition( -200, -200 );
		this->m_thisIsRightPaddle = false;
	}
	this->m_shape.setSize( { CONFIG_PADDLE_WIDTH, CONFIG_PADDLE_HEIGHT } );
	this->m_shape.setFillColor( sf::Color::White );
	this->m_shape.setOrigin( CONFIG_PADDLE_WIDTH / 2.f, CONFIG_PADDLE_HEIGHT / 2.f );
}

Paddle::~Paddle() {}

void Paddle::newRound()
{
	// reset paddle positions
	if ( this->m_thisIsRightPaddle ) {
		// this->m_shape.setPosition( ( SETTINGS->currentScreenSizeWidth - SETTINGS->paddleIndent ), SETTINGS->currentScreenSizeHeight / 2 );
		this->m_shape.setPosition( ( SETTINGS->currentScreenSizeWidth - SETTINGS->paddleIndent ), 74 );	// TODO delete this test hardcode
	} else {
		// this->m_shape.setPosition( SETTINGS->paddleIndent, SETTINGS->currentScreenSizeHeight / 2 );
		this->m_shape.setPosition( SETTINGS->paddleIndent, 133 );// TODO delete this test hardcode
	}
}

void Paddle::update( sf::Time timeSinceLastUpdate )
{
	if ( this->m_computerControlled ) {
		// TODO  delete this debug comment out of AI
		/*
		float	myTop = this->getTop();
		float	myBottom = this->getBottom();

		float	ballY = ball->getY();
		float	myY = this->getY();

		// do Computer-Player stuff here
		if ( ( ballY < myY ) && ( myTop > SETTINGS->playAreaTopLine ) ) {
		        sf::Vector2f moveDistance( ( 0.f ), ( moveDistance.y = CONFIG_PADDLE_MOVEMENT_NEG_STEP ) );
		        this->m_shape.move( moveDistance );
		} else if ( ( ballY > myY ) && ( myBottom < SETTINGS->playAreaBottomLine ) ) {
		        sf::Vector2f moveDistance( ( 0.f ), ( moveDistance.y = CONFIG_PADDLE_MOVEMENT_POS_STEP ) );
		        this->m_shape.move( moveDistance );
		*/
	} else {
		// do Human-Player stuff here
		processHumanMovement();
	}
}

void Paddle::draw( sf::RenderTarget &target, sf::RenderStates states ) const { target.draw( m_shape ); }

float Paddle::getX() const noexcept { return m_shape.getPosition().x; }

float Paddle::getY() const noexcept { return m_shape.getPosition().y; }

float Paddle::getTop() const noexcept { return getY() - m_shape.getSize().y / 2.f; }

float Paddle::getBottom() const noexcept { return getY() + m_shape.getSize().y / 2.f; }

float Paddle::getLeft()    const noexcept { return getX() - m_shape.getSize().x / 2.f; }

float Paddle::getRight()   const noexcept { return getX() + m_shape.getSize().x / 2.f; }

void Paddle::processHumanMovement()
{
	if ( GLOBALS->moveUpRequestActive ) {
		float myTop = this->getTop();
		if ( ( myTop - CONFIG_PADDLE_MOVEMENT_POS_STEP ) > SETTINGS->playAreaTopLine ) {
			sf::Vector2f moveDistance( ( 0.f ), ( CONFIG_PADDLE_MOVEMENT_NEG_STEP ) );
			this->m_shape.move( moveDistance );
		}
	}
	if ( GLOBALS->moveDownRequestActive ) {
		float myBottom = this->getBottom();
		if ( ( myBottom + CONFIG_PADDLE_MOVEMENT_POS_STEP ) < SETTINGS->playAreaBottomLine ) {
			sf::Vector2f moveDistance( ( 0.f ), ( CONFIG_PADDLE_MOVEMENT_POS_STEP ) );
			this->m_shape.move( moveDistance );
		}
	}
}

/* EOF */


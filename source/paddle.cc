/* paddle.cc */

#include <include/paddle.h>

extern Settings				SETTINGS;
extern std::unique_ptr <Globals>	GLOBALS;
extern std::unique_ptr <Ball>		ball;

Paddle::Paddle( bool thisIsRightPaddle )
{
	// ctor

	if ( thisIsRightPaddle ) {
		// position the right side paddle
		// this->m_shape.setPosition( ( ( SETTINGS.currentScreenSizeWidth ) - 50 ), 100 );
		this->m_shape.setPosition( -100, -100 );
		this->m_thisIsRightPaddle = true;
		std::cout << "\nCreated a RIGHT side paddle.\n";// TODO delete this debug line
	} else {
		// position the left side paddle
		// this->m_shape.setPosition( 50, 200 );
		this->m_shape.setPosition( -200, -200 );
		this->m_thisIsRightPaddle = false;
		std::cout << "Created a LEFT side paddle.\n";	// TODO delete this debug line
	}
	this->m_shape.setSize( { CONFIG_PADDLE_WIDTH, CONFIG_PADDLE_HEIGHT } );
	this->m_shape.setFillColor( sf::Color::White );
	this->m_shape.setOrigin( CONFIG_PADDLE_WIDTH / 2.f, CONFIG_PADDLE_HEIGHT / 2.f );

	// report for debugging // TODO remove this debug section
	sf::Vector2f v( ( this->m_shape.getPosition().x ), ( v.y = this->m_shape.getPosition().y ) );
	std::cerr << "Paddle [" << this << "] constructed at coordinates: " << std::to_string( v.x ) << "," << std::to_string( v.y ) << "\n\n";
}

Paddle::~Paddle()
{
	// dtor
	std::cerr << "Paddle [" << this << "] destructed\n";
}

void Paddle::newRound()
{
	// reset paddle positions
	if ( this->m_thisIsRightPaddle ) {
		this->m_shape.setPosition( ( SETTINGS.currentScreenSizeWidth - SETTINGS.paddleIndent ), SETTINGS.currentScreenSizeHeight / 2 );
	} else {
		this->m_shape.setPosition( SETTINGS.paddleIndent, SETTINGS.currentScreenSizeHeight / 2 );
	}
}

/*! Update a paddle
* \param val Delta time
*/
void Paddle::update( sf::Time timeSinceLastUpdate )
{
	if ( this->m_computerControlled ) {
		float	myTop = this->getTop();
		float	myBottom = this->getBottom();

		float	ballY = ball->getY();
		float	myY = this->getY();
		// std::cout << "=================================================================================\nPaddle observed ball.y is: " << ballTop << "\n";// TODO delete this debug line

		// do Computer-Player stuff here
		if ( ( ballY < myY ) && ( myTop > SETTINGS.playAreaTopLine ) ) {
			// NEED TO GO UP?
			sf::Vector2f moveDistance( ( 0.f ), ( moveDistance.y = CONFIG_PADDLE_MOVEMENT_NEG_STEP ) );
			this->m_shape.move( moveDistance );
			// std::cout << "\nPaddleComputer::update moved UP!\n";	// TODO delete this debug line
		} else if ( ( ballY > myY ) && ( myBottom < SETTINGS.playAreaBottomLine ) ) {
			// NEED TO GO DOWN?
			sf::Vector2f moveDistance( ( 0.f ), ( moveDistance.y = CONFIG_PADDLE_MOVEMENT_POS_STEP ) );
			this->m_shape.move( moveDistance );
			// std::cout << "\nPaddleComputer::update moved DOWN!\n";	// TODO delete this debug line
		} else {
			// std::cout << "\nPaddleComputer::update LAST ELSE HIT!\n";// TODO delete this debug line
			// std::cout << "ballTop/myTop = " << ballTop << "/" << myTop << "\t|\tballBottom/myBottom = " << ballBottom << "/" << myBottom << "\n";
		}
	} else {
		// do Human-Player stuff here
		processHumanMovement();
	}
}

/** Draw the shape on screen.
* \param tar Render target
* \param sta States
*/
void Paddle::draw( sf::RenderTarget &target, sf::RenderStates states ) const {
	// target.draw( this->m_shape );
	target.draw( m_shape );
}

float Paddle::getX() const noexcept
{
	return m_shape.getPosition().x;
}

float Paddle::getY() const noexcept
{
	return m_shape.getPosition().y;
}

float Paddle::getTop() const noexcept
{
	return getY() - m_shape.getSize().y / 2.f;
}

float Paddle::getBottom() const noexcept
{
	return getY() + m_shape.getSize().y / 2.f;
}

void Paddle::processHumanMovement()
{
	if ( GLOBALS->moveUpRequestActive ) {
		float myTop = this->getTop();
		if ( ( myTop - CONFIG_PADDLE_MOVEMENT_POS_STEP ) > SETTINGS.playAreaTopLine ) {
			sf::Vector2f moveDistance( ( 0.f ), ( CONFIG_PADDLE_MOVEMENT_NEG_STEP ) );
			this->m_shape.move( moveDistance );
		}
	}
	if ( GLOBALS->moveDownRequestActive ) {
		float myBottom = this->getBottom();
		if ( ( myBottom + CONFIG_PADDLE_MOVEMENT_POS_STEP ) < SETTINGS.playAreaBottomLine ) {
			sf::Vector2f moveDistance( ( 0.f ), ( CONFIG_PADDLE_MOVEMENT_POS_STEP ) );
			this->m_shape.move( moveDistance );
		}
	}
}

/* EOF */


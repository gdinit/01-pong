/* vec2d.h */

#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <math.h>

class Vector2D
{
	public:
		Vector2D( float X = 0, float Y = 0 )
		{
			x = X;
			y = Y;
		};
		~Vector2D() {};

		float x, y;

		Vector2D operator *( float scalar ) const
		{
			return Vector2D( x * scalar, y * scalar );
		}

		Vector2D operator +( const Vector2D &vect ) const
		{
			return Vector2D( x + vect.x, y + vect.y );
		}

		Vector2D operator -( const Vector2D &vect ) const
		{
			return Vector2D( x - vect.x, y - vect.y );
		}

		void rotate( float angle )
		{
			float	xt = ( x * cosf( angle ) ) - ( y * sinf( angle ) );
			float	yt = ( y * cosf( angle ) ) + ( x * sinf( angle ) );
			x = xt;
			y = yt;
		}

		float crossproduct( const Vector2D &vect2 ) const
		{
			return ( this->x * vect2.y ) - ( this->y * vect2.x );
		}

		float magnitude()
		{
			return sqrtf( x * x + y * y );
		}

		void normalize()
		{
			float mag = sqrtf( x * x + y * y );
			this->x = x / mag;
			this->y = y / mag;
		}

		// return dot product
		float dotproduct( const Vector2D &vect ) const
		{
			return ( x * vect.x ) + ( y * vect.y );
		}
};

#endif	// VECTOR2D_H

/* EOF */


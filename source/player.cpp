#include "player.h"

Player::Player(Vector2f _position)
	: position(_position), angle(0.f)
{
	;
}

void Player::update(u32 kDown)
{
	// use current angle for up and down.
	if (kDown & (KEY_UP | KEY_DOWN))
	{
		float dx = playerSpeed * cos(angle * (M_PI / 180));
		float dy = playerSpeed * sin(angle * (M_PI / 180));
		
		if (kDown & KEY_UP)
		{
			position.x += dx;
			position.y += dy;
		}
		if (kDown & KEY_DOWN)
		{
			position.x -= dx;
			position.y -= dy;
		}
	}

	// same thing for up and down except angle is rotated 90 degrees.
	if (kDown & (KEY_LEFT | KEY_RIGHT))
	{
		float dx = playerSpeed * cos((angle - 90.f) * (M_PI / 180));
		float dy = playerSpeed * sin((angle - 90.f) * (M_PI / 180));
		
		if (kDown & KEY_LEFT)
		{
			position.x += dx;
			position.y += dy;
		}
		if (kDown & KEY_RIGHT)
		{
			position.x -= dx;
			position.y -= dy;
		}
	}
	
	if (kDown & KEY_L)		angle -= rotationSpeed;
	if (kDown & KEY_R)		angle += rotationSpeed;

	angle = fmodf(angle, 360.f);
}

void Player::render()
{
	C2D_DrawCircleSolid(position.x, position.y, 1, playerRadius, playerColor);
}
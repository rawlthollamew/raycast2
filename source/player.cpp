#include "player.h"

Player::Player(Vector2f _position)
	: position(_position), angle(0.f)
{
	;
}

void Player::update(u32 _kDown)
{
	// use current angle for up and down.
	if (_kDown & (KEY_UP | KEY_DOWN))
	{
		float dx = playerSpeed * cos(angle * (M_PI / 180));
		float dy = playerSpeed * sin(angle * (M_PI / 180));

		if (_kDown & KEY_UP)
		{
			collision(position, {position.x + dx, position.y});
			collision(position, {position.x, position.y + dy});
		}
		if (_kDown & KEY_DOWN)
		{
			collision(position, {position.x - dx, position.y});
			collision(position, {position.x, position.y - dy});
		}
	}
	
	// same thing for up and down except angle is rotated 90 degrees.
	if (_kDown & (KEY_LEFT | KEY_RIGHT))
	{
		float dx = playerSpeed * cos((angle - 90.f) * (M_PI / 180));
		float dy = playerSpeed * sin((angle - 90.f) * (M_PI / 180));
		
		if (_kDown & KEY_LEFT)
		{
			collision(position, {position.x + dx, position.y});
			collision(position, {position.x, position.y + dy});
		}
		if (_kDown & KEY_RIGHT)
		{
			collision(position, {position.x - dx, position.y});
			collision(position, {position.x, position.y - dy});
		}
	}
	
	if (_kDown & KEY_L)		angle -= rotationSpeed;
	if (_kDown & KEY_R)		angle += rotationSpeed;

	angle = fmodf(angle, 360.f);
}

void Player::render()
{
	C2D_DrawCircleSolid(position.x, position.y, 1, playerRadius, playerColor);
}

void Player::collision(Vector2f _currentPosition, Vector2f _newPosition)
{
	Vector2i mapPosition = {
		(int)C2D_Clamp(_newPosition.x / tileSize, 0, tileDimentions - 1),
		(int)C2D_Clamp(_newPosition.y / tileSize, 0, tileDimentions - 1)
	};

	if (!Map::hit(mapPosition))
	{
		position = _newPosition;
	}
}
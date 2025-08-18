#include "player.h"

Player::Player(Vector2f _position)
	: position(_position), angle(0.f)
{
	;
}

void Player::update(u32 kDown)
{
	if (kDown & KEY_UP) 	position.y -= playerSpeed;
	if (kDown & KEY_DOWN) 	position.y += playerSpeed;
	if (kDown & KEY_LEFT) 	position.x -= playerSpeed;
	if (kDown & KEY_RIGHT) 	position.x += playerSpeed;

	if (kDown & KEY_L)		angle -= rotationSpeed;
	if (kDown & KEY_R)		angle += rotationSpeed;

	angle = fmodf(angle, 360.f);
}

void Player::render()
{
	C2D_DrawCircleSolid(position.x, position.y, 1, playerRadius, playerColor);
}
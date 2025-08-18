#include "player.h"

const float playerSpeed = 0.2f;
const int playerRadius = 4;

const u32 clrGreen = C2D_Color32(0x00, 0xFF, 0x00, 0xFF);

Player::Player(float _startX, float _startY)
	: positionX(_startX), positionY(_startY)
{
	;
}

void Player::update(u32 kDown)
{
	if (kDown & KEY_LEFT) 	positionX -= playerSpeed;
	if (kDown & KEY_RIGHT) 	positionX += playerSpeed;

	if (kDown & KEY_UP) 	positionY -= playerSpeed;
	if (kDown & KEY_DOWN) 	positionY += playerSpeed;
}

void Player::render()
{
	C2D_DrawCircleSolid(positionX * tileSize, positionY * tileSize, 1, playerRadius, clrGreen);
}
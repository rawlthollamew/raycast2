#include "player.h"

const int playerSpeed = 1;
const int playerRadius = 10;
const u32 clrGreen = C2D_Color32(0x00, 0xFF, 0x00, 0xFF);

Player::Player(float _startX, float _startY)
	: positionX(_startX), positionY(_startY)
{
	;
}

void Player::update(u32 kDown)
{
	if (kDown & KEY_LEFT)
	{
		
	}
}

void Player::render()
{
	C2D_DrawCircleSolid(positionX, positionY, 1000, playerRadius, clrGreen);
}
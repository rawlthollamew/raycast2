#pragma once
#include <citro2d.h>
#include <3ds.h>

class Player
{
public:
	Player(float _startX, float _startY);
	
	float positionX;
	float positionY;
	
	void update(u32 kDown);
	void render();
};
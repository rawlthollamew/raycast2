#pragma once
#include <citro2d.h>
#include <3ds.h>
#include "map.h"
#include "utils.h"

const float playerSpeed = 1.f;
const int playerRadius = 4;
const float rotationSpeed = 1.5f;

const u32 playerColor = C2D_Color32f(1.f, 1.f, 0.f, 1.f);

class Player
{
public:
	Player(Vector2f _position);
	
	Vector2f position;
	float angle;
	
	void update(u32 _kDown);
	void render();
private:
	void collision(Vector2f _currentPosition, Vector2f _newPosition);
};
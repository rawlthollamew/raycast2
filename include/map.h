#pragma once
#include <citro2d.h>

const int tileDimentions = 10;

const int tileMap[tileDimentions][tileDimentions] = 
{
	{1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,1,0,1},
	{1,0,0,0,0,0,0,1,0,1},
	{1,0,0,0,0,0,1,1,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1},
};

// For best fit (bottom screen height is 240)
const int tileSize = (int)(240 / tileDimentions);

const int wallColor = C2D_Color32f(1.f, 1.f, 1.f, 0.5f);

class Map
{
public:
    static bool hit(int mapX, int mapY);
    static void render();
};
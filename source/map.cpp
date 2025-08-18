#include "map.h"

const int tileMap[10][10] = 
{
	{1,1,1,1,1,1,1,1,1,1},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
};

const int tileSize = 16;

u32 clrWhite = C2D_Color32(0xFF, 0xFF, 0xFF, 0xFF);

bool Map::hit(int mapX, int mapY)
{
	if (tileMap[mapY][mapX] > 0) return true;
	else return false;
}

void Map::render()
{
	for (int x = 0; x < 10; x++)
	{
		for (int y = 0; y < 10; y++)
		{
			if (tileMap[y][x] > 0)
			{
				C2D_DrawRectSolid(x * tileSize, y * tileSize, 0, tileSize, tileSize, clrWhite);
			}
		}
	}
}
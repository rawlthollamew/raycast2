#include "map.h"

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
				C2D_DrawRectSolid(x * tileSize, y * tileSize, 0, tileSize, tileSize, wallColor);
			}
		}
	}
}
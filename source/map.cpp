#include "map.h"

bool Map::hit(Vector2i _position)
{
	if (tileMap[_position.y][_position.x] > 0) return true;
	else return false;
}

void Map::render()
{
	for (int x = 0; x < mapDimentions.x; x++)
	{
		for (int y = 0; y < mapDimentions.y; y++)
		{
			if (tileMap[y][x] > 0)
			{
				C2D_DrawRectSolid(x * tileSize, y * tileSize, 0, tileSize, tileSize, wallColor);
			}
		}
	}
}
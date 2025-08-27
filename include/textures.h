#pragma once
#include <citro2d.h>
#include <3ds.h>
#include <string>

enum TileInfo
{
	BlankTile,
	WallTile,
	CatTile
};

enum TextureOrder
{
	BrickTexture,
	CatTexture,
	FloorTexture,
	SkyboxTexture,
};

class Textures
{
public:
	Textures(char* _filename)
	{
		sheet = C2D_SpriteSheetLoad(_filename);
	}
	C2D_SpriteSheet sheet;
};
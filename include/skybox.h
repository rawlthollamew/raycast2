#pragma once
#include <citro2d.h>
#include <3ds.h>
#include "textures.h"
#include "map.h"

class Skybox
{
public:
	Skybox(C2D_SpriteSheet _sheet);
	void draw(Vector2i _screenSize, float _angle);
private:
	C2D_Sprite skyboxSprite;
	C2D_Sprite floorSprite;
};
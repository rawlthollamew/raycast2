#pragma once
#include <vector>
#include "map.h"
#include "utils.h"
#include "textures.h"

const int viewDistance = 300;

// raycount needs to be a factor of screenwidth (400(wanna do 800 but cannot.))
const int rayCount = 400;
const int playerFov = 100;

const int spriteDimentions = 64;
const int sliceCount = spriteDimentions;

class Ray
{
public:
	Ray();
	Ray(float _angle, Vector2f _position);
	float angle;
	Vector2f position;

	float distance;
	Vector2i tileHit;
	Vector2f hitPosition;
	int sliceIndex;

	void update();
};

class RayManager
{
public:
	RayManager(C2D_SpriteSheet _sheet);
	std::vector<Ray> rays;
	
	void update(Vector2f _position, float _angle);
	void drawRays();
	void drawWalls(Vector2i screenSize, float angle);
private:
	void sliceSprite(C2D_Sprite* _currentSprite, int _slice);
	
	C2D_Sprite brickSprite;
	C2D_Sprite catSprite;
	C2D_Sprite skyboxSprite;
	C2D_Sprite floorSprite;
};
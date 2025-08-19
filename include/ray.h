#pragma once
#include <vector>
#include <optional>
#include "map.h"
#include "utils.h"

const int viewDistance = 300;
const int sliceCount = 16;
const u32 lineColor = C2D_Color32f(0.f, 1.f, 0.f, 1.f);

const int rayCount = 100;
const int playerFov = 100;

const int spriteDimentions = 64;

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
	RayManager();
	std::vector<Ray> rays;
	
	void update(Vector2f _position, float _angle);
	void drawRays();
	void drawWalls(Vector2i screenSize, float angle);
private:
	void sliceSprite(C2D_Sprite& _currentSprite, int _slice);
	
	C2D_Sprite brickSprite;
	C2D_Sprite catSprite;
	C2D_Sprite ceilingSprite;
	C2D_Sprite floorSprite;
};
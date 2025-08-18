#pragma once
#include <vector>
#include "map.h"

class Ray
{
public:
	Ray(float positionX, float positionY, float angle);
	int distance;
	float angle;
};

class RayManager
{
public:
	RayManager(int _rayCount);
	std::vector<Ray> rays;
	void update();
private:
	int rayCount;
};
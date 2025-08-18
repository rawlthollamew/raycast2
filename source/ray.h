#pragma once
#include <vector>
#include "map.h"

class Ray
{
public:
	Ray(float _angle);

	float distance;
	float angle;

	void calculate();
};

class RayManager
{
public:
	RayManager(int _rayCount);
	std::vector<Ray> rays;
	void update();
	void render();
private:
	int rayCount;
};
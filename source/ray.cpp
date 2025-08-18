#include "ray.h"

Ray::Ray()
	: angle(0.f), distance(-1.f), sliceIndex(-1)
{
	tileHit = { -1, -1 };
	position = { 0.f, 0.f };
	hitPosition = { 0.f, 0.f };
}


Ray::Ray(float _angle, Vector2f _position)
	: angle(_angle), position(_position), distance(-1.f), sliceIndex(-1)
{
	tileHit = { -1, -1 };
	update();
}


void Ray::update()
{
	// using principles borrowed from https://lodev.org/cgtutor/raycasting.html
	// specifically the part on the DDA algorithm

	Vector2f rayDirection = {
		cosf(angle),
		sinf(angle)
	};
	
	Vector2f deltaDistance = {
		fabs(1.0f / rayDirection.x) * tileSize,
		fabs(1.0f / rayDirection.y) * tileSize
	};
	
	Vector2i mapPosition = {
		(int)C2D_Clamp(position.x / tileSize, 0, tileDimentions - 1),
		(int)C2D_Clamp(position.y / tileSize, 0, tileDimentions - 1)
	};

	Vector2i stepDirection = {
		(rayDirection.x < 0) ? -1 : 1,
		(rayDirection.y < 0) ? -1 : 1
	};
	
	Vector2f sideDistance = {
		(rayDirection.x < 0)
			? (position.x - mapPosition.x * tileSize) * deltaDistance.x / tileSize
			: ((mapPosition.x + 1) * tileSize - position.x) * deltaDistance.x / tileSize,
		(rayDirection.y < 0)
			? (position.y - mapPosition.y * tileSize) * deltaDistance.y / tileSize
			: ((mapPosition.y + 1) * tileSize - position.y) * deltaDistance.y / tileSize
	};

	while (distance == -1.f)
	{
		bool hitVertical = (sideDistance.x < sideDistance.y);

		if (hitVertical)
		{
			mapPosition.x += stepDirection.x;
			sideDistance.x += deltaDistance.x;
		}
		else
		{
			mapPosition.y += stepDirection.y;
			sideDistance.y += deltaDistance.y;
		}

		// in this case it will never hit. 
		if (mapPosition.y < 0 || mapPosition.y >= tileDimentions || mapPosition.x < 0 || mapPosition.x >= tileDimentions) distance = viewDistance;
		
		// in this case it will hit.
		if (tileMap[(int)(mapPosition.y)][(int)(mapPosition.x)] > 0)
		{
			float hitDistance = hitVertical ? (sideDistance.x - deltaDistance.x) : (sideDistance.y - deltaDistance.y);
			
			hitPosition = {
				position.x + rayDirection.x * hitDistance,
				position.y + rayDirection.y * hitDistance
			};
			
			if (tileHit.x == -1.f && tileHit.y == -1.f) tileHit = { mapPosition.x, mapPosition.y };

			if (sliceIndex == -1)
			{
				sliceIndex = hitVertical
					? (int)(fmod(hitPosition.y, tileSize) / tileSize * sliceCount) + 1
					: (int)(fmod(hitPosition.x, tileSize) / tileSize * sliceCount) + 1;
			}
			distance = hitDistance;
		}
		if (sideDistance.x > viewDistance && sideDistance.y > viewDistance) distance = viewDistance;
	}
	if (distance == -1.f) distance = 0.f;
}

RayManager::RayManager()
{
	;
}

void RayManager::update(Vector2f _position, float _angle)
{
	rays.resize(rayCount);

	for (int i = 0; i < rayCount; i++)
	{
		float fovRad = playerFov * (M_PI / 180.f);
		float angleRad = _angle * (M_PI / 180.f);

		float rayAngle = angleRad - (fovRad * 0.5f) + ((float)i / (rayCount - 1)) * fovRad;
		Ray newray(rayAngle, _position);
		rays[i] = newray;
	}
}

void RayManager::drawRays()
{
	for (int i = 0; i < rayCount; i++)
	{
		C2D_DrawLine(rays[i].position.x, rays[i].position.y, lineColor, rays[i].hitPosition.x, rays[i].hitPosition.y, lineColor, 1, 1);
	}
}

void RayManager::drawWalls(Vector2i _screenSize, float _angle)
{
	// Using the logic from https://lodev.org/cgtutor/raycasting.html
	
	float fovRad = playerFov * (M_PI / 180.f);
	float angleRad = _angle * (M_PI / 180.f);
	float projectionPlaneDistance = (_screenSize.x / 2.f) / tan(fovRad / 2.f);

	for (int i = 0; i < rayCount; i++)
	{
		float currentRayAngle = angleRad - (fovRad / 2.f) + ((float)i / (rayCount - 1)) * fovRad;
		float correctedDistance = rays[i].distance * cos(currentRayAngle - angleRad);

		int sliceWidth = _screenSize.x / rayCount;
		int wallHeight = (int)((tileSize * projectionPlaneDistance) / correctedDistance);

		Vector2i wallPosition = {
			i * sliceWidth,
			(_screenSize.y / 2) - (wallHeight / 2)
		};

		// rectangle format
		// calculates the alpha of the wall, 1 when close, 0 when far.
		float wallAlpha = (float)wallHeight / (float)_screenSize.y;
		if (wallAlpha > 1.f) wallAlpha = 1.f;

		u32 newWallColor = C2D_Color32f(1.f, 1.f, 1.f, wallAlpha);

		C2D_DrawRectSolid(wallPosition.x, wallPosition.y, 0, sliceWidth, wallHeight, newWallColor);
	}
}

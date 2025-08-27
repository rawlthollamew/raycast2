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

	// we need to keep track of which side the ray hit, being the x or y for the wall distance.

	Vector2f rayDirection = {
		cosf(angle),
		sinf(angle)
	};
	
	Vector2f deltaDistance = {
		fabs(1.0f / rayDirection.x) * tileSize,
		fabs(1.0f / rayDirection.y) * tileSize
	};
	
	Vector2i mapPosition = {
		(int)C2D_Clamp(position.x / tileSize, 0, mapDimentions.x - 1),
		(int)C2D_Clamp(position.y / tileSize, 0, mapDimentions.y - 1)
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
		if (mapPosition.y < 0 || mapPosition.y >= mapDimentions.y || mapPosition.x < 0 || mapPosition.x >= mapDimentions.y) distance = viewDistance;
		
		// in this case it will hit.
		if (tileMap[(int)(mapPosition.y)][(int)(mapPosition.x)] > 0)
		{
			distance = hitVertical
				? sideDistance.x - deltaDistance.x
				: sideDistance.y - deltaDistance.y;
			
			hitPosition = {
				position.x + rayDirection.x * distance,
				position.y + rayDirection.y * distance
			};
			
			if (tileHit.x == -1.f && tileHit.y == -1.f) tileHit = { mapPosition.x, mapPosition.y };

			if (sliceIndex == -1)
			{
				sliceIndex = hitVertical
					? (int)(fmod(hitPosition.y, tileSize) / tileSize * sliceCount) + 1
					: (int)(fmod(hitPosition.x, tileSize) / tileSize * sliceCount) + 1;
			}
		}
		if (sideDistance.x > viewDistance && sideDistance.y > viewDistance) distance = viewDistance;
	}
	if (distance == -1.f) distance = 0.f;
}

RayManager::RayManager(C2D_SpriteSheet _sheet)
{
	C2D_SpriteFromSheet(&brickSprite,	_sheet, BrickTexture);
	C2D_SpriteFromSheet(&catSprite,		_sheet, CatTexture);
	C2D_SpriteFromSheet(&skyboxSprite,	_sheet, SkyboxTexture);
	C2D_SpriteFromSheet(&floorSprite,	_sheet, FloorTexture);
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
	u32 lineColor = C2D_Color32f(0.f, 1.f, 0.f, 1.f);
	u32 debugColor = C2D_Color32f(1.f, 0.f, 0.f, 1.f);

	for (int i = 0; i < rayCount; i++)
	{
		if (i == rayCount / 2) 
		{
			C2D_DrawLine(
				rays[i].position.x,
				rays[i].position.y,
				debugColor,
				rays[i].hitPosition.x,
				rays[i].hitPosition.y,
				debugColor,
				5,
				1
			);
		}
		else
		{
			C2D_DrawLine(
				rays[i].position.x,
				rays[i].position.y,
				lineColor,
				rays[i].hitPosition.x,
				rays[i].hitPosition.y,
				lineColor,
				1,
				1
			);
		}
	}

	C2D_DrawRectSolid(
		rays[rayCount / 2].tileHit.x * tileSize,
		rays[rayCount / 2].tileHit.y * tileSize,
		0,
		tileSize,
		tileSize,
		debugColor
	);
}

void RayManager::drawWalls(Vector2i _screenSize, float _angle)
{
	// Using the logic from https://lodev.org/cgtutor/raycasting.html
	
	float fovRad = playerFov * (M_PI / 180.f);
	float angleRad = _angle * (M_PI / 180.f);

	for (int i = 0; i < rayCount; i++)
	{
		// float correctedDistance = rays[i].distance * cos(rays[i].angle - angleRad);
		
		// to avoid dividing by 0 later on.
		// if (correctedDistance < 0.1f) correctedDistance = 0.1f;

		// support for widerays 
		float rayWidth = _screenSize.x / rayCount;
		float wallHeight = spriteDimentions / rays[i].distance;
		// float rayScreenX = tan(rays[i].angle - angleRad) * projectionPlaneDistance;

		Vector2f wallPosition = {
			rayWidth * i,
			// (_screenSize.x / 2) + rayScreenX,
			(_screenSize.y / 2) - (wallHeight / 2)
		};

		// // rectangle format
		// // calculates the alpha of the wall, 1 when close, 0 when far.
		// float wallAlpha = (float)wallHeight / (float)_screenSize.y;
		// if (wallAlpha > 1.f) wallAlpha = 1.f;
		
		// u32 newWallColor = C2D_Color32f(1.f, 1.f, 1.f, wallAlpha);
		
		// C2D_DrawRectSolid(wallPosition.x, wallPosition.y, 0, sliceWidth, wallHeight, newWallColor);

		// sprite format
		C2D_Sprite currentSprite;

		if (tileMap[rays[i].tileHit.y][rays[i].tileHit.x] == WallTile) currentSprite = brickSprite;
		else if (tileMap[rays[i].tileHit.y][rays[i].tileHit.x] == CatTile) currentSprite = catSprite;
		else currentSprite = floorSprite;

		C2D_SpriteSetCenter(&currentSprite, 0.f, 0.5f);
		sliceSprite(&currentSprite, rays[i].sliceIndex);
		C2D_SpriteSetPos(&currentSprite, wallPosition.x, wallPosition.y);
		C2D_SpriteSetScale(&currentSprite, rayWidth, wallHeight);
		C2D_DrawSprite(&currentSprite);
	}
}

void RayManager::sliceSprite(C2D_Sprite* _currentSprite, int _slice)
{
	C2D_Sprite tempSprite = *_currentSprite;
	Tex3DS_SubTexture* newSubtex = new Tex3DS_SubTexture();

	// top, bottom and height are all going to be the same.
	newSubtex->top = tempSprite.image.subtex->top;
	newSubtex->bottom = tempSprite.image.subtex->bottom;
	newSubtex->width = spriteDimentions / sliceCount;
	newSubtex->height = spriteDimentions;
	
	if (_slice == sliceCount)
	{
		// special case to prevent out of bounds
		// this get the initialized subtex variables and increments it from the slice index, taking into account uv.
		// derived from ((1 / sliceCount) * slice) / 2
		newSubtex->left = tempSprite.image.subtex->left + (((1.f / sliceCount) * (_slice  - 1)) / 2);
		newSubtex->right = tempSprite.image.subtex->left + (((1.f / sliceCount) * _slice) / 2);
	}
	else
	{
		newSubtex->left = tempSprite.image.subtex->left + (((1.f / sliceCount) * _slice) / 2);
		newSubtex->right = tempSprite.image.subtex->left + (((1.f / sliceCount) * (_slice + 1)) / 2);
	}

	tempSprite.image.subtex = newSubtex;
	*_currentSprite = tempSprite;
}
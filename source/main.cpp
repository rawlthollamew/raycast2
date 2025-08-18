#include <citro2d.h>
#include <3ds.h>

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "map.h"
#include "player.h"
#include "utils.h"
#include "ray.h"

const Vector2i topScreen = { 400, 240 };
const Vector2i bottomScreen = { 320, 240};
const Vector2f startPosition = { 2.f * tileSize, 2.f * tileSize };

int main(int argc, char* argv[])
{
	gfxInitDefault();
	C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
	C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
	C2D_Prepare();

	C3D_RenderTarget* top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);
	C3D_RenderTarget* bottom = C2D_CreateScreenTarget(GFX_BOTTOM, GFX_LEFT);

	u32 clrBlack = C2D_Color32(0x00, 0x00, 0x00, 0xFF);

	Player player(startPosition);
	RayManager rayManager;

	while (aptMainLoop())
	{
		hidScanInput();

		u32 kHeld = hidKeysHeld();
		if (kHeld & KEY_START) break;
		
		player.update(kHeld);
		rayManager.update(player.position, player.angle);
		
		C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
			C2D_TargetClear(top, clrBlack);
			C2D_SceneBegin(top);
			rayManager.drawWalls(topScreen);
			
			C2D_TargetClear(bottom, clrBlack);
			C2D_SceneBegin(bottom);
			Map::render();
			rayManager.drawRays();
			player.render();
		C3D_FrameEnd(0);
	}

	// Deinit libs
	C2D_Fini();
	C3D_Fini();
	gfxExit();
	return 0;
}
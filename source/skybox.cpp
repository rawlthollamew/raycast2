#include "skybox.h"

Skybox::Skybox(C2D_SpriteSheet _sheet)
{
    C2D_SpriteFromSheet(&skyboxSprite, _sheet, SkyboxTexture);
}

void Skybox::draw(Vector2i _screenSize, float _angle)
{
    // bruh 64 dont fit well in 400
    int spriteDimentions = 64;

    // rotate the skybox in the sky when the player looks around
    // C2D_SpriteSetPos(&skyboxSprite, 0.f, 0.f);
    // C2D_SpriteSetPos(&floorSprite, 0.f, _screenSize.y / 2.f);
    // C2D_SpriteSetScale(&skyboxSprite, _screenSize.x / spriteDimentions, (_screenSize.y / 2.f) / spriteDimentions);
    // C2D_SpriteSetScale(&floorSprite, _screenSize.x / spriteDimentions, (_screenSize.y / 2.f) / spriteDimentions);

    C2D_DrawRectSolid(0, 0, 0, _screenSize.x, _screenSize.y / 2.f, C2D_Color32(153, 217, 234, 255));
    C2D_DrawRectSolid(0, _screenSize.y / 2.f, 0, _screenSize.x, _screenSize.y / 2.f, C2D_Color32(182, 120, 86, 255));

    // C2D_DrawSprite(&skyboxSprite);
    // C2D_DrawSprite(&floorSprite);
}

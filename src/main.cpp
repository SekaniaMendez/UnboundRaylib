#include "controls/ControlDirectional.hpp"
#include <raylib.h>

int main() {
  const int screenWidth = 1440;
  const int screenHeight = 980;
  InitWindow(screenWidth, screenHeight, "UnboundRayLib - Texture test");
  SetTargetFPS(60);

  // Load texture from the working directory.
  // Make sure character.png is in the project root (where you run ./game).
  Texture2D character = LoadTexture("character.png");

  Vector2 pos = {(float)screenWidth / 2 - character.width / 2.0f,
                 (float)screenHeight / 2 - character.height / 2.0f};

  ControlDirectional control(240.0f);

  while (!WindowShouldClose()) {
    control.Update(GetFrameTime(), pos, screenWidth, screenHeight,
                   character.width, character.height);

    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawTexture(character, (int)pos.x, (int)pos.y, WHITE);
    DrawText("Press ESC to quit", 20, 20, 20, DARKGRAY);
    EndDrawing();
  }

  UnloadTexture(character); // free GPU memory
  CloseWindow();            // close window/context
  return 0;
}
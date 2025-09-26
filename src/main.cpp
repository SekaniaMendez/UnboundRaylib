#include "camera/PlayerCamera.hpp"
#include "controls/ControlDirectional.hpp"
#include <math.h>
#include <raylib.h>

static inline void DrawGridCentered(Vector3 center, int slices, float spacing) {
  // Draw lines parallel to X and Z axes around `center` on Y=0 plane
  const int half = slices / 2;
  const float y = 0.0f;
  for (int i = -half; i <= half; ++i) {
    float offset = i * spacing;
    // Lines parallel to X (varying Z)
    DrawLine3D({center.x - half * spacing, y, center.z + offset},
               {center.x + half * spacing, y, center.z + offset},
               (i == 0) ? DARKGRAY : LIGHTGRAY);
    // Lines parallel to Z (varying X)
    DrawLine3D({center.x + offset, y, center.z - half * spacing},
               {center.x + offset, y, center.z + half * spacing},
               (i == 0) ? DARKGRAY : LIGHTGRAY);
  }
}

static inline void DrawWorldGridWindow(Vector3 cameraPos, float halfExtent,
                                       float spacing) {
  // World-aligned grid on Y=0 plane. Lines are fixed at multiples of `spacing`
  // in world space.
  const float y = 0.0f;
  const float startX = floorf((cameraPos.x - halfExtent) / spacing) * spacing;
  const float endX = floorf((cameraPos.x + halfExtent) / spacing) * spacing;
  const float startZ = floorf((cameraPos.z - halfExtent) / spacing) * spacing;
  const float endZ = floorf((cameraPos.z + halfExtent) / spacing) * spacing;

  for (float x = startX; x <= endX; x += spacing) {
    Color c = (fabsf(x) < 1e-4f) ? DARKGRAY : LIGHTGRAY; // emphasize world X=0
    DrawLine3D({x, y, startZ}, {x, y, endZ}, c);
  }
  for (float z = startZ; z <= endZ; z += spacing) {
    Color c = (fabsf(z) < 1e-4f) ? DARKGRAY : LIGHTGRAY; // emphasize world Z=0
    DrawLine3D({startX, y, z}, {endX, y, z}, c);
  }
}

int main() {
  const int screenWidth = 1240;
  const int screenHeight = 780;
  InitWindow(screenWidth, screenHeight, "UnboundRayLib - Texture test");
  SetTargetFPS(60);

  // Load texture from the working directory.
  // Make sure character.png is in the project root (where you run ./game).
  Texture2D character = LoadTexture("character.png");

  Vector2 pos = {(float)screenWidth / 2 - character.width / 2.0f,
                 (float)screenHeight / 2 - character.height / 2.0f};

  Vector3 player3D = {pos.x, 0.0f, pos.y};

  ControlDirectional control(240.0f);
  PlayerCamera &playerCam = PlayerCamera::CamInstance(player3D);

  while (!WindowShouldClose()) {
    control.Update(GetFrameTime(), pos, screenWidth, screenHeight,
                   character.width, character.height);
    player3D = {pos.x, 0.0f, pos.y};
    playerCam.Update(player3D);

    BeginDrawing();
    ClearBackground(RAYWHITE);

    BeginMode3D(playerCam.GetCamera());
    // World-aligned static grid (appears fixed in the world)
    DrawWorldGridWindow(playerCam.GetCamera().position, 100.0f, 1.0f);
    DrawCube(player3D, 2.0f, 2.0f, 2.0f, RED);
    DrawPlane({0.0f, -1.0f, 0.0f}, {100.0f, 100.0f}, LIGHTGRAY);

    // Axis helpers: X (red), Y (green), Z (blue)
    DrawLine3D({0.0f, 0.0f, 0.0f}, {20.0f, 0.0f, 0.0f}, RED);   // +X
    DrawLine3D({0.0f, 0.0f, 0.0f}, {0.0f, 20.0f, 0.0f}, GREEN); // +Y
    DrawLine3D({0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 20.0f}, BLUE);  // +Z

    // Wireframe to better see motion
    DrawCubeWires(player3D, 2.2f, 2.2f, 2.2f, BLACK);

    DrawGrid(10, 0.5f);
    EndMode3D();

    DrawText("Press ESC to quit", 20, 20, 20, DARKGRAY);
    DrawText(TextFormat("2D Pos (screen): x=%.1f  y=%.1f", pos.x, pos.y), 20,
             46, 18, DARKGRAY);
    DrawText(TextFormat("3D Pos (world):  X=%.1f  Y=%.1f  Z=%.1f", player3D.x,
                        player3D.y, player3D.z),
             20, 68, 18, DARKGRAY);
    EndDrawing();
  }

  UnloadTexture(character); // free GPU memory
  CloseWindow();            // close window/context
  return 0;
}
#pragma once
#include <raylib.h>

class PlayerCamera {
private:
  Camera3D camera = {0};
  float cameraHeight = 45.0f;
  float cameraDistance = 50.0f;
  PlayerCamera(Vector3 PlayerPosition);

public:
  PlayerCamera(const PlayerCamera &) = delete;

  PlayerCamera &operator=(const PlayerCamera &) = delete;

  ~PlayerCamera();

  static PlayerCamera &CamInstance(Vector3 PlayerPosition);

  void Update(Vector3 playerPosition);
  Camera3D GetCamera() const { return camera; }
};

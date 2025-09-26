#include "PlayerCamera.hpp"

PlayerCamera::PlayerCamera(Vector3 playerPosition) {
  camera.position = {playerPosition.x, playerPosition.y,
                     playerPosition.z + cameraDistance};
  camera.target = playerPosition;
  camera.up = (Vector3){0.0, 1.0, 0.0};
  camera.fovy = 45.0;
  camera.projection = CAMERA_PERSPECTIVE;
}

PlayerCamera::~PlayerCamera() {}

void PlayerCamera::Update(Vector3 playerPosition) {
  camera.position = {playerPosition.x, playerPosition.y + cameraHeight,
                     playerPosition.z + cameraDistance};
  camera.target = playerPosition;
}

PlayerCamera &PlayerCamera::CamInstance(Vector3 PlayerPosition) {
  static PlayerCamera instance(PlayerPosition);
  return instance;
}
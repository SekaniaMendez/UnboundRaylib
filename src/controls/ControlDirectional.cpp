/**
 * @file ControlDirectional.cpp
 * @brief Implementation of the high-level movement controller based on
 * Directional input.
 *
 * Applies per-frame keyboard input (WASD/Arrows) to a 2D position using an
 * 8-way enum (MoveDirection). Diagonals are normalized by 1/sqrt(2) so speed
 * remains constant in any direction. Optional clamping keeps the sprite fully
 * visible on screen.
 *
 * @author Giovanni Daniel Mendez Sanchez (SekaniaMendez)
 * @date 2025-09-25
 * @copyright All rights reserved
 */

#include "ControlDirectional.hpp" // ControlDirectional declaration
#include "Directional.hpp"        // Directional & MoveDirection
#include <raylib.h>

// ------------------------
// Ctor / configuration
// ------------------------
ControlDirectional::ControlDirectional(float speed)
    : dir_(), dirEnum_(MoveDirection::None), speed_(speed) {}

void ControlDirectional::SetSpeed(float s) { speed_ = s; }
float ControlDirectional::GetSpeed() const { return speed_; }
MoveDirection ControlDirectional::GetDirection() const { return dirEnum_; }

// ------------------------
// Per-frame update
// ------------------------
void ControlDirectional::Update(float dt, Vector2 &pos, int screenW,
                                int screenH, int texW, int texH) {
  // 1) Sample input and resolve 8-way direction
  dirEnum_ = dir_.Update();

  // 2) Map enum to movement vector (diagonal normalized)
  Vector2 move = {0.0f, 0.0f};
  static constexpr float INV_SQRT2 = 0.70710678f; // 1/sqrt(2)
  switch (dirEnum_) {
  case MoveDirection::None:
    move = {0.0f, 0.0f};
    break;
  case MoveDirection::Left:
    move = {-1.0f, 0.0f};
    break;
  case MoveDirection::Right:
    move = {1.0f, 0.0f};
    break;
  case MoveDirection::Up:
    move = {0.0f, -1.0f};
    break;
  case MoveDirection::Down:
    move = {0.0f, 1.0f};
    break;
  case MoveDirection::UpLeft:
    move = {-INV_SQRT2, -INV_SQRT2};
    break;
  case MoveDirection::UpRight:
    move = {INV_SQRT2, -INV_SQRT2};
    break;
  case MoveDirection::DownLeft:
    move = {-INV_SQRT2, INV_SQRT2};
    break;
  case MoveDirection::DownRight:
    move = {INV_SQRT2, INV_SQRT2};
    break;
  }

  // 3) Integrate 2D position with constant speed
  pos.x += move.x * speed_ * dt;
  pos.y += move.y * speed_ * dt;

  // 6) Optional clamping (only if screen/texture sizes were provided)
  if (screenW > 0 && screenH > 0 && texW >= 0 && texH >= 0) {
    if (pos.x < 0.0f)
      pos.x = 0.0f;
    if (pos.y < 0.0f)
      pos.y = 0.0f;
    float maxX = (float)screenW - (float)texW;
    float maxY = (float)screenH - (float)texH;
    if (pos.x > maxX)
      pos.x = maxX;
    if (pos.y > maxY)
      pos.y = maxY;
  }
}
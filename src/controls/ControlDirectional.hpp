/****
 * @file Control.hpp
 * @brief High-level movement controller that applies Directional input to move
 * an entity.
 *
 * Orchestrates per-frame input sampling and movement integration. It queries
 * the keyboard through Directional (WASD/Arrow keys), converts the 8-way
 * enum into a movement vector (diagonals normalized by 1/sqrt(2)), and
 * updates a given position with speed * dt. Optional screen clamping is
 * supported to keep the sprite visible.
 *
 * Usage:
 *  - Construct ControlDirectional with a movement speed.
 *  - Call Update(dt, pos, screenW, screenH, texW, texH) each frame.
 *  - Query GetDirection() for animation/orientation.
 *
 * @author Giovanni Daniel Mendez Sanchez (SekaniaMendez)
 * @date 2025-09-25
 * @copyright All rights reserved
 */
#pragma once
#include "ControlDirectional.hpp"
#include "Directional.hpp"
#include <raylib.h>

/**
 * @class ControlDirectional
 * @brief Applies Directional input to update a 2D position with constant-speed
 * 8-way movement.
 */
class ControlDirectional {
public:
  /**
   * @brief Construct a movement controller.
   * @param speed Movement speed in pixels per second.
   */
  explicit ControlDirectional(float speed = 0.0f);
  /**
   * @brief Update movement for the current frame.
   *
   * Samples keyboard (via Directional), converts to a movement vector
   * with diagonal normalization, and applies `speed * dt` to the provided
   * position. If screen bounds and texture size are provided, the position
   * will be clamped to stay fully on screen.
   *
   * @param dt Delta time in seconds for this frame.
   * @param pos In/Out world/screen position to update.
   * @param screenW Optional screen width in pixels (for clamping). Use 0 to
   * skip.
   * @param screenH Optional screen height in pixels (for clamping). Use 0 to
   * skip.
   * @param texW Optional texture width in pixels (for clamping). Use 0 to skip.
   * @param texH Optional texture height in pixels (for clamping). Use 0 to
   * skip.
   */
  void Update(float dt, Vector2 &pos, int screenW = 0, int screenH = 0,
              int texW = 0, int texH = 0);
  /**
   * @brief Get the last resolved 8-way direction for the current frame.
   */
  MoveDirection GetDirection() const;
  /**
   * @brief Set movement speed in pixels per second.
   */
  void SetSpeed(float s);

  /**
   * @brief Get movement speed in pixels per second.
   */
  float GetSpeed() const;

private:
  Directional dir_; ///< Low-level directional input
  MoveDirection dirEnum_ =
      MoveDirection::None; ///< Cached direction for the frame
  float speed_ = 0.0f;     ///< Movement speed in px/s

  // --- One-shot jump (no gravity): applies a vertical offset only on the frame
  // Space is pressed ---
  bool isJumping_ = false;     // true only on the frame Space is pressed
  float jumpY_ = 0.0f;         // vertical offset to apply this frame
  float jumpImpulse_ = 650.0f; // visual jump height (one-shot)
};

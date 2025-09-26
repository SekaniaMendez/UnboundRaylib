/**
 * @file Directional.cpp
 * @brief Implementation of the keyboard-based 8-way directional input helper.
 *
 * This module reads raw keyboard input from raylib (WASD and Arrow keys),
 * resolves opposite inputs (e.g., A + D), and maps the result to a discrete
 * 8-way movement direction represented by the enum ::MoveDirection.
 *
 * Usage pattern:
 *  - Call Directional::Update() once per frame to read and resolve inputs.
 *  - Use the returned ::MoveDirection to drive movement/animation.
 *
 * @author Giovanni Daniel Mendez Sanchez (SekaniaMendez)
 * @date 2025-09-25
 * @copyright All rights reserved
 */
#include "Directional.hpp"
#include <raylib.h>

/**
 * @brief Default constructor.
 *
 * Initializes a Directional input helper. No resources are allocated.
 */
Directional::Directional() {}

/**
 * @brief Destructor.
 *
 * Frees any internal resources if they were used in future extensions.
 */
Directional::~Directional() {}

/**
 * @brief Samples keyboard state and resolves a discrete 8-way direction.
 *
 * Reads the current state of WASD and Arrow keys via raylib (`IsKeyDown`).
 * Opposite directions on the same axis cancel each other (e.g., Left+Right →
 * 0). The resulting horizontal (h) and vertical (v) components are mapped to
 * one of the eight ::MoveDirection values plus ::MoveDirection::None when (h,v)
 * == (0,0).
 *
 * @note This method should be called once per frame before using the direction.
 * @return ::MoveDirection The resolved movement direction for the current
 * frame.
 */
MoveDirection Directional::Update() {
  MoveDirection currentDirection = MoveDirection::None;
  // 1) Sample raw keys into private booleans
  moveLeft = IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT);
  moveRight = IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT);
  moveUp = IsKeyDown(KEY_W) || IsKeyDown(KEY_UP);
  moveDown = IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN);

  // 2) Resolve opposite keys (cancel axis if both pressed)
  int h = (moveRight ? 1 : 0) -
          (moveLeft ? 1 : 0); // +1 right, -1 left, 0 both/none
  int v = (moveDown ? 1 : 0) - (moveUp ? 1 : 0); // +1 down, -1 up, 0 both/none

  // 3) Map to enum (8-way)
  if (IsKeyDown(KEY_Q)) {
    currentDirection = MoveDirection::UpLeft;
  } else if (IsKeyDown(KEY_E)) {
    currentDirection = MoveDirection::UpRight;
  } else if (IsKeyDown(KEY_Z)) {
    currentDirection = MoveDirection::DownLeft;
  } else if (IsKeyDown(KEY_C)) {
    currentDirection = MoveDirection::DownRight;
  } else if (h == 0 && v == 0) {
    currentDirection = MoveDirection::None;
  } else if (h < 0 && v == 0) {
    currentDirection = MoveDirection::Left;
  } else if (h > 0 && v == 0) {
    currentDirection = MoveDirection::Right;
  } else if (h == 0 && v < 0) {
    currentDirection = MoveDirection::Up;
  } else if (h == 0 && v > 0) {
    currentDirection = MoveDirection::Down;
  } else if (h < 0 && v < 0) {
    currentDirection = MoveDirection::UpLeft;
  } else if (h > 0 && v < 0) {
    currentDirection = MoveDirection::UpRight;
  } else if (h < 0 && v > 0) {
    currentDirection = MoveDirection::DownLeft;
  } else { // h > 0 && v > 0
    currentDirection = MoveDirection::DownRight;
  }

  return currentDirection;
}

/**
 * @file Directional.hpp
 * @brief Declaration of the keyboard-based 8-way directional input helper.
 *
 * This header defines the ::MoveDirection enum and the Directional class,
 * which encapsulate input handling for WASD and Arrow keys, mapping them
 * into one of eight discrete directions plus None.
 *
 * Usage:
 *  - Call Directional::Update() once per frame.
 *  - Use the returned ::MoveDirection to drive movement and animations.
 *
 * @author Giovanni Daniel Mendez Sanchez (SekaniaMendez)
 * @date 2025-09-25
 * @copyright All rights reserved
 */
#pragma once

#include <raylib.h>

// Enum that represents the current movement direction
enum class MoveDirection {
  None,
  Left,
  Right,
  Up,
  Down,
  UpLeft,
  UpRight,
  DownLeft,
  DownRight
};

class Directional {
public:
  Directional();
  ~Directional();

  // Update the private booleans and set the current direction
  MoveDirection Update();

private:
  // Internal booleans used only for calculating movement
  bool moveLeft;
  bool moveRight;
  bool moveUp;
  bool moveDown;
};
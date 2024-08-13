#ifndef NBODY_SRC_CORE_INPUT_
#define NBODY_SRC_CORE_INPUT_

#include "Events/key_codes.h"
#include "glm/gtc/type_ptr.hpp"

class Input {
public:
  static Input &GetInstance();

  static bool IsKeyPressed(KeyCode key);
  static bool IsKeyReleased(KeyCode key);
  static bool IsMouseButtonPressed(MouseCode button);
  static float GetMouseX();
  static float GetMouseY();
  static glm::vec2 GetMousePosition();

  static void TogleMouseCursor(bool enabled);
  static void SetMousePosition(float x, float y);
};

#endif // NBODY_SRC_CORE_INPUT_

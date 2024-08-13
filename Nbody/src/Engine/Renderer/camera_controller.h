#ifndef NBODY_SRC_RENDERER_CAMERA_CONTROLLER_
#define NBODY_SRC_RENDERER_CAMERA_CONTROLLER_

#include "Events/mouse_events.h"
#include "Events/window_events.h"
#include "camera.h"

class OrthographicCameraController {
public:
  OrthographicCameraController(float aspect_ratio, bool rotation = false);

  void OnUpdate(float ts);
  void OnEvent(Event &e);

  OrthographicCamera &GetCamera() { return camera_; }
  const OrthographicCamera &GetCamera() const { return camera_; }

  float GetZoomLevel() const { return zoom_level_; }
  void SetZoomLevel(float level) { zoom_level_ = level; }

private:
  bool OnMouseScrolled(MouseScrolledEvent &e);
  bool OnWindowResized(WindowResizeEvent &e);

private:
  float aspect_ratio_;
  float zoom_level_ = 1.0f;
  OrthographicCamera camera_;

  bool rotation_;

  glm::vec3 camera_position_ = {0.0f, 0.0f, 0.0f};
  float camera_rotation_ = 0.0f; // In degrees, in the anti-clockwise direction
  float camera_translation_speed_ = 5.0f;
  float camera_rotation_speed_ = 180.0f;
};

class CameraController {
public:
  CameraController(float fov, float aspect_ratio, float near_clip,
                   float far_clip);

  void OnUpdate(float ts);
  void OnEvent(Event &e);

  void Enable();
  void Disable();
  bool IsEnabled();

  EditorCamera &GetCamera() { return camera_; }
  const EditorCamera &GetCamera() const { return camera_; }

private:
  bool OnMouseScrolled(MouseScrolledEvent &e);
  bool OnWindowResized(WindowResizeEvent &e);

private:
  bool is_enabled_ = false;
  float aspect_ratio_;
  float fov_;
  float near_clip_;
  float far_clip_;

  EditorCamera camera_;

  float mouse_position_x_ = 0;
  float mouse_position_y_ = 0;

  float yaw_ = 0.0f;
  float pitch_ = 0.0f;
  glm::vec3 camera_position_ = {0.0f, 0.0f, 0.0f};
  float camera_translation_speed_ = 5.0f;
  float mouse_sensitivity_ = 5.0;
};

#endif // NBODY_SRC_RENDERER_CAMERA_CONTROLLER_

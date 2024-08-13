#include "camera_controller.h"
#include "Core/application.h"
#include "Core/input.h"
#include "Core/log.h"
#include "Events/event_dispatcher.h"
#include "Events/key_codes.h"
#include "camera.h"

OrthographicCameraController::OrthographicCameraController(float aspectRatio,
                                                           bool rotation)
    : aspect_ratio_(aspectRatio),
      camera_(-aspect_ratio_ * zoom_level_, aspect_ratio_ * zoom_level_,
              -zoom_level_, zoom_level_),
      rotation_(rotation) {}

void OrthographicCameraController::OnUpdate(float ts) {
  if (Input::IsKeyPressed(Key::A)) {
    LOG_GLOBAL_INFO("Camera moved");
    camera_position_.x -=
        cos(glm::radians(camera_rotation_)) * camera_translation_speed_ * ts;
    camera_position_.y -=
        sin(glm::radians(camera_rotation_)) * camera_translation_speed_ * ts;

  } else if (Input::IsKeyPressed(Key::D)) {
    LOG_GLOBAL_INFO("Camera moved");
    camera_position_.x +=
        cos(glm::radians(camera_rotation_)) * camera_translation_speed_ * ts;
    camera_position_.y +=
        sin(glm::radians(camera_rotation_)) * camera_translation_speed_ * ts;
  }

  if (Input::IsKeyPressed(Key::W)) {
    LOG_GLOBAL_INFO("Camera moved");
    camera_position_.x +=
        -sin(glm::radians(camera_rotation_)) * camera_translation_speed_ * ts;
    camera_position_.y +=
        cos(glm::radians(camera_rotation_)) * camera_translation_speed_ * ts;

  } else if (Input::IsKeyPressed(Key::S)) {
    LOG_GLOBAL_INFO("Camera moved");
    camera_position_.x -=
        -sin(glm::radians(camera_rotation_)) * camera_translation_speed_ * ts;
    camera_position_.y -=
        cos(glm::radians(camera_rotation_)) * camera_translation_speed_ * ts;
  }

  if (rotation_) {
    if (Input::IsKeyPressed(Key::Q))
      camera_rotation_ += camera_rotation_speed_ * ts;
    if (Input::IsKeyPressed(Key::E))
      camera_rotation_ -= camera_rotation_speed_ * ts;

    if (camera_rotation_ > 180.0f)
      camera_rotation_ -= 360.0f;
    else if (camera_rotation_ <= -180.0f)
      camera_rotation_ += 360.0f;

    camera_.SetRotation(camera_rotation_);
  }

  camera_.SetPosition(camera_position_);
  camera_translation_speed_ = zoom_level_;
}

void OrthographicCameraController::OnEvent(Event &e) {
  EventDispatcher dispatcher(e);

  dispatcher.Dispatch<MouseScrolledEvent>(
      BIND_EVENT(OrthographicCameraController::OnMouseScrolled));
  dispatcher.Dispatch<WindowResizeEvent>(
      BIND_EVENT(OrthographicCameraController::OnWindowResized));
}

bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent &e) {
  zoom_level_ -= e.GetYOffset() * 0.25f;
  zoom_level_ = std::max(zoom_level_, 0.25f);
  camera_.SetProjection(-aspect_ratio_ * zoom_level_,
                        aspect_ratio_ * zoom_level_, -zoom_level_, zoom_level_);
  return false;
}

bool OrthographicCameraController::OnWindowResized(WindowResizeEvent &e) {
  aspect_ratio_ = (float)e.GetWidth() / (float)e.GetHeight();
  camera_.SetProjection(-aspect_ratio_ * zoom_level_,
                        aspect_ratio_ * zoom_level_, -zoom_level_, zoom_level_);
  return false;
}

// EditorCamera

CameraController::CameraController(float fov, float aspect_ratio,
                                   float near_clip, float far_clip)
    : aspect_ratio_(aspect_ratio), fov_(fov), near_clip_(near_clip),
      far_clip_(far_clip), camera_(fov, aspect_ratio_, near_clip, far_clip) {}

void CameraController::OnUpdate(float ts) {
  if (!is_enabled_)
    return;

  if (Input::IsKeyPressed(Key::A)) {
    camera_position_ -=
        camera_.GetRightDirection() * camera_translation_speed_ * ts;

  } else if (Input::IsKeyPressed(Key::D)) {
    camera_position_ +=
        camera_.GetRightDirection() * camera_translation_speed_ * ts;
  }

  if (Input::IsKeyPressed(Key::W)) {
    camera_position_ +=
        camera_.GetForwardDirection() * camera_translation_speed_ * ts;

  } else if (Input::IsKeyPressed(Key::S)) {
    camera_position_ -=
        camera_.GetForwardDirection() * camera_translation_speed_ * ts;
  }

  if (Input::IsKeyPressed(Key::Space)) {
    camera_position_.y += camera_translation_speed_ * ts;
  } else if (Input::IsKeyPressed(Key::LeftShift)) {
    camera_position_.y -= camera_translation_speed_ * ts;
  }

  if (Input::IsKeyPressed(Key::Up)) {
    pitch_ += mouse_sensitivity_ * 10 * ts;
  } else if (Input::IsKeyPressed(Key::Down)) {
    pitch_ -= mouse_sensitivity_ * 10 * ts;
  }

  if (Input::IsKeyPressed(Key::Right)) {
    yaw_ += mouse_sensitivity_ * 10 * ts;
  } else if (Input::IsKeyPressed(Key::Left)) {
    yaw_ -= mouse_sensitivity_ * 10 * ts;
  }

  float current_mouse_position_x = Input::GetMouseX();
  float current_mouse_position_y = Input::GetMouseY();

  yaw_ -=
      (mouse_position_x_ - current_mouse_position_x) * mouse_sensitivity_ * ts;
  pitch_ +=
      (mouse_position_y_ - current_mouse_position_y) * mouse_sensitivity_ * ts;

  mouse_position_x_ = current_mouse_position_x;
  mouse_position_y_ = current_mouse_position_y;

  camera_.SetPosition(camera_position_);

  if (pitch_ > 89.0f)
    pitch_ = 89.0f;
  if (pitch_ < -89.0f)
    pitch_ = -89.0f;

  camera_.SetYaw(yaw_);
  camera_.SetPitch(pitch_);

  camera_.OnUpdate(ts);

  /* Input::SetMousePosition( */
  /*     static_cast<float>(Application::GetInstance().GetWindow().GetWidth()) /
   * 2, */
  /*     static_cast<float>(Application::GetInstance().GetWindow().GetHeight())
   * / */
  /*         2); */
}

void CameraController::OnEvent(Event &e) {
  EventDispatcher dispatcher(e);

  dispatcher.Dispatch<MouseScrolledEvent>(
      BIND_EVENT(CameraController::OnMouseScrolled));
  dispatcher.Dispatch<WindowResizeEvent>(
      BIND_EVENT(CameraController::OnWindowResized));
}

bool CameraController::OnMouseScrolled(MouseScrolledEvent &e) {
  camera_.SetProjection(fov_, aspect_ratio_, near_clip_, far_clip_);
  return false;
}

bool CameraController::OnWindowResized(WindowResizeEvent &e) {
  aspect_ratio_ = (float)e.GetWidth() / (float)e.GetHeight();
  camera_.SetProjection(fov_, aspect_ratio_, near_clip_, far_clip_);
  return false;
}

void CameraController::Enable() {
  is_enabled_ = true;
  Input::TogleMouseCursor(false);
}
void CameraController::Disable() {
  is_enabled_ = false;
  Input::TogleMouseCursor(true);
}
bool CameraController::IsEnabled() { return is_enabled_; }

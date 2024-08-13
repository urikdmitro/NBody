#ifndef NBODY_SRC_RENDERER_CAMERA_
#define NBODY_SRC_RENDERER_CAMERA_

#include "Events/event.h"
#include "Events/mouse_events.h"
#include "glm/glm.hpp"

class SceneCamera {
public:
  enum class ProjectionType { Perspective = 0, Orthographic = 1 };

public:
  SceneCamera();
  virtual ~SceneCamera() = default;

  void SetPerspective(float verticalFOV, float nearClip, float farClip);
  void SetOrthographic(float size, float nearClip, float farClip);

  void SetViewportSize(uint32_t width, uint32_t height);

  float GetPerspectiveVerticalFOV() const { return m_PerspectiveFOV; }
  void SetPerspectiveVerticalFOV(float verticalFov) {
    m_PerspectiveFOV = verticalFov;
    RecalculateProjection();
  }
  float GetPerspectiveNearClip() const { return m_PerspectiveNear; }
  void SetPerspectiveNearClip(float nearClip) {
    m_PerspectiveNear = nearClip;
    RecalculateProjection();
  }
  float GetPerspectiveFarClip() const { return m_PerspectiveFar; }
  void SetPerspectiveFarClip(float farClip) {
    m_PerspectiveFar = farClip;
    RecalculateProjection();
  }

  float GetOrthographicSize() const { return m_OrthographicSize; }
  void SetOrthographicSize(float size) {
    m_OrthographicSize = size;
    RecalculateProjection();
  }
  float GetOrthographicNearClip() const { return m_OrthographicNear; }
  void SetOrthographicNearClip(float nearClip) {
    m_OrthographicNear = nearClip;
    RecalculateProjection();
  }
  float GetOrthographicFarClip() const { return m_OrthographicFar; }
  void SetOrthographicFarClip(float farClip) {
    m_OrthographicFar = farClip;
    RecalculateProjection();
  }

  ProjectionType GetProjectionType() const { return m_ProjectionType; }
  void SetProjectionType(ProjectionType type) {
    m_ProjectionType = type;
    RecalculateProjection();
  }

private:
  void RecalculateProjection();

private:
  glm::mat4 m_Projection;
  ProjectionType m_ProjectionType = ProjectionType::Perspective;

  float m_PerspectiveFOV = glm::radians(45.0f);
  float m_PerspectiveNear = 0.01f, m_PerspectiveFar = 1000.0f;

  float m_OrthographicSize = 10.0f;
  float m_OrthographicNear = -1.0f, m_OrthographicFar = 1.0f;

  float m_AspectRatio = 0.0f;
};

class EditorCamera {
public:
  EditorCamera() = default;
  EditorCamera(float fov, float aspectRatio, float nearClip, float farClip);

  void SetProjection(float fov, float aspectRatio, float nearClip,
                     float farClip);

  void OnUpdate(float ts);

  inline void SetPosition(glm::vec3 position) { position_ = position; }

  const glm::mat4 &GetViewMatrix() const { return view_matrix_; }
  glm::mat4 GetViewProjection() const { return projection_ * view_matrix_; }

  glm::vec3 GetUpDirection() const;
  glm::vec3 GetRightDirection() const;
  glm::vec3 GetForwardDirection() const;
  const glm::vec3 &GetPosition() const { return position_; }

  float GetPitch() const { return pitch_; }
  float GetYaw() const { return yaw_; }

  void SetPitch(float pitch) {
    if (pitch > 89.0f)
      pitch = 89.0f;
    if (pitch < -89.0f)
      pitch = -89.0f;
    pitch_ = pitch;
  }
  void SetYaw(float yaw) { yaw_ = yaw; }

private:
  void UpdateProjection();
  void UpdateView();

  float fov_ = 45.0f, aspect_ratio_ = 1.778f, near_clip_ = 0.1f,
        far_clip_ = 1000.0f;

  glm::mat4 projection_;
  glm::mat4 view_matrix_;
  glm::vec3 position_ = {0.0f, 0.0f, 0.0f};
  glm::vec3 forward_ = {0.0f, 0.0f, 0.0f};
  glm::vec3 right_ = {0.0f, 0.0f, 0.0f};
  glm::vec3 up_ = {0.0f, 0.0f, 0.0f};

  float pitch_ = 0.0f, yaw_ = 0.0f;
};

class OrthographicCamera {
public:
  OrthographicCamera(float left, float right, float bottom, float top);

  void SetProjection(float left, float right, float bottom, float top);

  const glm::vec3 &GetPosition() const;
  void SetPosition(const glm::vec3 &position);

  float GetRotation() const;
  void SetRotation(float rotation);

  const glm::mat4 &GetProjectionMatrix() const;
  const glm::mat4 &GetViewMatrix() const;
  const glm::mat4 &GetViewProjectionMatrix() const;

private:
  void RecalculateViewMatrix_();

  glm::mat4 projection_matrix_;
  glm::mat4 view_matrix_;
  glm::mat4 view_projection_matrix_;

  glm::vec3 position_ = {0.0f, 0.0f, 0.0f};
  float rotation_ = 0.0f;
};

#endif // NBODY_SRC_RENDERER_CAMERA_

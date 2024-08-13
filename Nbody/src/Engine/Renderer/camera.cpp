#include "camera.h"
#include "Core/input.h"
#include "Events/event_dispatcher.h"
#include "Events/key_codes.h"
#include "glm/ext/matrix_transform.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtx/quaternion.hpp>
#include <utility>

SceneCamera::SceneCamera() { RecalculateProjection(); }

void SceneCamera::SetPerspective(float verticalFOV, float nearClip,
                                 float farClip) {
  m_ProjectionType = ProjectionType::Perspective;
  m_PerspectiveFOV = verticalFOV;
  m_PerspectiveNear = nearClip;
  m_PerspectiveFar = farClip;
  RecalculateProjection();
}

void SceneCamera::SetOrthographic(float size, float nearClip, float farClip) {
  m_ProjectionType = ProjectionType::Orthographic;
  m_OrthographicSize = size;
  m_OrthographicNear = nearClip;
  m_OrthographicFar = farClip;
  RecalculateProjection();
}

void SceneCamera::SetViewportSize(uint32_t width, uint32_t height) {
  m_AspectRatio = (float)width / (float)height;
  RecalculateProjection();
}

void SceneCamera::RecalculateProjection() {
  if (m_ProjectionType == ProjectionType::Perspective) {
    m_Projection = glm::perspective(m_PerspectiveFOV, m_AspectRatio,
                                    m_PerspectiveNear, m_PerspectiveFar);
  } else {
    float orthoLeft = -m_OrthographicSize * m_AspectRatio * 0.5f;
    float orthoRight = m_OrthographicSize * m_AspectRatio * 0.5f;
    float orthoBottom = -m_OrthographicSize * 0.5f;
    float orthoTop = m_OrthographicSize * 0.5f;

    m_Projection = glm::ortho(orthoLeft, orthoRight, orthoBottom, orthoTop,
                              m_OrthographicNear, m_OrthographicFar);
  }
}

void EditorCamera::SetProjection(float fov, float aspectRatio, float nearClip,
                                 float farClip) {
  fov_ = fov;
  aspect_ratio_ = aspectRatio;
  near_clip_ = nearClip;
  far_clip_ = farClip;
}

EditorCamera::EditorCamera(float fov, float aspectRatio, float nearClip,
                           float farClip)
    : fov_(fov), aspect_ratio_(aspectRatio), near_clip_(nearClip),
      far_clip_(farClip),
      projection_(
          glm::perspective(glm::radians(fov), aspectRatio, nearClip, farClip)) {

  UpdateView();
}

void EditorCamera::OnUpdate(float ts) {
  UpdateProjection();
  UpdateView();
}

void EditorCamera::UpdateProjection() {
  /* aspect_ratio_ = viewport_width_ / viewport_height_; */
  projection_ = glm::perspective(glm::radians(fov_), aspect_ratio_, near_clip_,
                                 far_clip_);
}

void EditorCamera::UpdateView() {
  glm::vec3 forward;
  forward.x = cos(glm::radians(yaw_)) * cos(glm::radians(pitch_));
  forward.y = sin(glm::radians(pitch_));
  forward.z = sin(glm::radians(yaw_)) * cos(glm::radians(pitch_));

  forward_ = glm::normalize(forward);
  right_ = glm::normalize(glm::cross(forward_, glm::vec3(0.0f, 1.0f, 0.0f)));
  up_ = glm::normalize(glm::cross(right_, forward_));

  view_matrix_ = glm::lookAt(position_, position_ + forward_, up_);
}

glm::vec3 EditorCamera::GetUpDirection() const { return up_; }

glm::vec3 EditorCamera::GetRightDirection() const { return right_; }

glm::vec3 EditorCamera::GetForwardDirection() const { return forward_; }

//

OrthographicCamera::OrthographicCamera(float left, float right, float bottom,
                                       float top)
    : projection_matrix_(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)),
      view_matrix_(1.0f) {

  view_projection_matrix_ = projection_matrix_ * view_matrix_;
}

void OrthographicCamera::SetProjection(float left, float right, float bottom,
                                       float top) {
  projection_matrix_ = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
  view_projection_matrix_ = projection_matrix_ * view_matrix_;
}

void OrthographicCamera::RecalculateViewMatrix_() {
  glm::mat4 transform =
      glm::translate(glm::mat4(1.0f), position_) *
      glm::rotate(glm::mat4(1.0f), glm::radians(rotation_), glm::vec3(0, 0, 1));

  view_matrix_ = glm::inverse(transform);
  view_projection_matrix_ = projection_matrix_ * view_matrix_;
}

const glm::vec3 &OrthographicCamera::GetPosition() const { return position_; }

void OrthographicCamera::SetPosition(const glm::vec3 &position) {
  position_ = position;
  RecalculateViewMatrix_();
}

float OrthographicCamera::GetRotation() const { return rotation_; }
void OrthographicCamera::SetRotation(float rotation) {
  rotation_ = rotation;
  RecalculateViewMatrix_();
}

const glm::mat4 &OrthographicCamera::GetProjectionMatrix() const {
  return projection_matrix_;
}

const glm::mat4 &OrthographicCamera::GetViewMatrix() const {
  return view_matrix_;
}

const glm::mat4 &OrthographicCamera::GetViewProjectionMatrix() const {
  return view_projection_matrix_;
}

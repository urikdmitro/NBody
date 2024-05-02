#include <iostream>

#include "texture.h"

Texture2D::Texture2D(GLuint width, GLuint height)
    : width_(width), height_(height) {
  glGenTextures(1, &id_);
}

void Texture2D::LoadImage(unsigned char *pixel_data) {

  glBindTexture(GL_TEXTURE_2D, id_);
  // TODO: get Image_Format and Internal_Format through parameter
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width_, height_, 0, GL_RGB,
               GL_UNSIGNED_BYTE, pixel_data);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glBindTexture(GL_TEXTURE_2D, 0);
}

GLuint Texture2D::GetWidth() { return width_; }
GLuint Texture2D::GetHeight() { return height_; }

void Texture2D::Bind() { glBindTexture(GL_TEXTURE_2D, id_); }

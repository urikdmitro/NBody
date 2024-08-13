#include "opengl_texture.h"
#include "vendor/stb/stb_image.h"
#include <glad/glad.h>

static GLenum ImageFormatToGLDataFormat(ImageFormat format) {
  switch (format) {
  case ImageFormat::RGB8:
    return GL_RGB;
  case ImageFormat::RGBA8:
    return GL_RGBA;
  default:
    return 0;
  }
}

static GLenum ImageFormatToGLInternalFormat(ImageFormat format) {
  switch (format) {
  case ImageFormat::RGB8:
    return GL_RGB8;
  case ImageFormat::RGBA8:
    return GL_RGBA8;
  default:
    return 0;
  }
}

const TextureSpecification &OpenGLTexture::GetSpecification() const {
  return specification_;
}

int OpenGLTexture::GetWidth() const { return width_; }
int OpenGLTexture::GetHeight() const { return height_; }
int OpenGLTexture::GetID() const { return id_; }

const std::string &OpenGLTexture::GetPath() const { return path_; }

bool OpenGLTexture::IsLoaded() const { return is_loaded_; }

OpenGLTexture::OpenGLTexture(const TextureSpecification &specification)
    : specification_(specification), width_(specification_.width),
      height_(specification.height) {

  internal_format_ = ImageFormatToGLInternalFormat(specification.format);
  data_format_ = ImageFormatToGLDataFormat(specification.format);

  glCreateTextures(GL_TEXTURE_2D, 1, &id_);
  glTextureStorage2D(id_, 1, internal_format_, width_, height_);

  glTextureParameteri(id_, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTextureParameteri(id_, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glTextureParameteri(id_, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTextureParameteri(id_, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

OpenGLTexture::OpenGLTexture(const std::string &path) : path_(path) {

  int width, height, channels;
  stbi_set_flip_vertically_on_load(1);
  stbi_uc *data = nullptr;
  { data = stbi_load(path.c_str(), &width, &height, &channels, 0); }

  if (data) {
    is_loaded_ = true;

    width_ = width;
    height_ = height;

    GLenum internalFormat = 0, dataFormat = 0;
    if (channels == 4) {
      internalFormat = GL_RGBA8;
      dataFormat = GL_RGBA;
    } else if (channels == 3) {
      internalFormat = GL_RGB8;
      dataFormat = GL_RGB;
    }

    internal_format_ = internalFormat;
    data_format_ = dataFormat;

    glCreateTextures(GL_TEXTURE_2D, 1, &id_);
    glTextureStorage2D(id_, 1, internalFormat, width_, height_);

    glTextureParameteri(id_, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(id_, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTextureParameteri(id_, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(id_, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTextureSubImage2D(id_, 0, 0, 0, width_, height_, data_format_,
                        GL_UNSIGNED_BYTE, data);

    stbi_image_free(data);
  }
}

OpenGLTexture::~OpenGLTexture() { glDeleteTextures(1, &id_); }

void OpenGLTexture::SetData(void *data, size_t size) {

  uint32_t bpp = data_format_ == GL_RGBA ? 4 : 3;
  glTextureSubImage2D(id_, 0, 0, 0, width_, height_, data_format_,
                      GL_UNSIGNED_BYTE, data);
}

void OpenGLTexture::Bind(size_t slot) const { glBindTextureUnit(slot, id_); }

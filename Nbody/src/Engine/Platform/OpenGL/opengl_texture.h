#ifndef NBODY_SRC_RENDERER_OPENGL_TEXTURE
#define NBODY_SRC_RENDERER_OPENGL_TEXTURE

#include "Renderer/texture.h"
#include <glad/glad.h>

class OpenGLTexture : public Texture {
public:
  OpenGLTexture(const TextureSpecification &specification);
  OpenGLTexture(const std::string &path);
  ~OpenGLTexture();

  const TextureSpecification &GetSpecification() const override;

  int GetWidth() const override;
  int GetHeight() const override;
  int GetID() const override;

  const std::string &GetPath() const override;

  void SetData(void *data, size_t size) override;
  void Bind(size_t slot = 0) const override;
  bool IsLoaded() const override;

private:
  TextureSpecification specification_;
  std::string path_;
  bool is_loaded_ = false;
  GLuint width_, height_;
  GLuint id_;
  GLenum internal_format_, data_format_;
};

#endif // NBODY_SRC_RENDERER_OPENGL_TEXTURE

#ifndef NBODY_SRC_RENDERER_TEXTURE
#define NBODY_SRC_RENDERER_TEXTURE

#include <glad/glad.h>

class Texture2D {
private:
  GLuint id_;
  GLuint width_;
  GLuint height_;

public:
  // TODO: do smt with defaul constructor
  // TODO: create destructor
  Texture2D() = default;
  Texture2D(GLuint width, GLuint height);

  GLuint GetWidth();
  GLuint GetHeight();

  void LoadImage(unsigned char *pixel_data);

  void Bind();
};

#endif // NBODY_SRC_RENDERER_TEXTURE

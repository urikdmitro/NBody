#ifndef NBODY_SRC_RENDERER_TEXTURE
#define NBODY_SRC_RENDERER_TEXTURE

#include <glad/glad.h>
#include <string>

enum class ImageFormat { None = 0, R8, RGB8, RGBA8, RGBA32F };

struct TextureSpecification {
  int width = 1;
  int height = 1;
  ImageFormat format = ImageFormat::RGBA8;
  bool have_to_generate_mipmaps = true;
};

class Texture {
public:
  virtual ~Texture();

  virtual const TextureSpecification &GetSpecification() const = 0;

  virtual int GetWidth() const = 0;
  virtual int GetHeight() const = 0;
  virtual int GetID() const = 0;

  virtual const std::string &GetPath() const = 0;

  virtual void SetData(void *data, size_t size) = 0;
  virtual void Bind(size_t slot = 0) const = 0;
  virtual bool IsLoaded() const = 0;

  static Texture *Create(const std::string &path);
  static Texture *Create(const TextureSpecification &specification);
};

#endif // NBODY_SRC_RENDERER_TEXTURE

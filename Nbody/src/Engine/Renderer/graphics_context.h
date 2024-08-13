#ifndef NBODY_SRC_RENDERER_GRAPHICS_CONTEXT_
#define NBODY_SRC_RENDERER_GRAPHICS_CONTEXT_

class GraphicsContext {
public:
  virtual void Init() = 0;
  virtual void SwapBuffers() = 0;
  virtual ~GraphicsContext();
};

#endif // NBODY_SRC_RENDERER_GRAPHICS_CONTEXT_

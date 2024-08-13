#ifndef NBODY_SRC_PROGRAM_MESH_
#define NBODY_SRC_PROGRAM_MESH_

#include "Renderer/vertex_array.h"

class IMesh {
public:
  virtual ~IMesh() {}
  virtual VertexArray *GetVertexArray() = 0;
};

class SphereMesh : public IMesh {
public:
  ~SphereMesh();

  VertexArray *GetVertexArray() override;
};

class CubeMesh : public IMesh {
private:
public:
  ~CubeMesh();

  VertexArray *GetVertexArray() override;
};

#endif

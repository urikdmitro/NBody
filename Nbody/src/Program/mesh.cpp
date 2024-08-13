#include "mesh.h"
#include "Renderer/index_buffer.h"
#include "Renderer/vertex_array.h"
#include "Renderer/vertex_buffer.h"
#include "glm/glm.hpp"
#include "math.h"

CubeMesh::~CubeMesh() {}
VertexArray *CubeMesh::GetVertexArray() {

  float vertices[] = {
      -1, 1,  -1, //
      1,  1,  -1, //
      -1, -1, -1, //
      1,  -1, -1, //
      -1, 1,  1,  //
      1,  1,  1,  //
      -1, -1, 1,  //
      1,  -1, 1   //
  };

  unsigned int elements[] = {0, 1, 2, // Side 0
                             2, 1, 3, //
                             4, 0, 6, // Side 1
                             6, 0, 2, //
                             7, 5, 6, // Side 2
                             6, 5, 4, //
                             3, 1, 7, // Side 3
                             7, 1, 5, //
                             4, 5, 0, // Side 4
                             0, 5, 1, //
                             3, 7, 2, // Side 5
                             2, 7, 6};

  IndexBuffer *ib = IndexBuffer::Create(elements, sizeof(elements));
  VertexBuffer *vb = VertexBuffer::Create(vertices, sizeof(vertices));
  vb->SetLayout(BufferLayout({BufferElement(ShaderDataType::Float3, "cube")}));

  VertexArray *va = VertexArray::Create();
  va->AddVertexBuffer(vb);
  va->SetIndexBuffer(ib);

  return va;
}
#define AddFace(i1, i2, i3)                                                    \
  {                                                                            \
    indices.push_back(i1);                                                     \
    indices.push_back(i2);                                                     \
    indices.push_back(i3);                                                     \
  }

#define AddFaces(i1, i2, i3, i4)                                               \
  {                                                                            \
    indices.push_back(i1);                                                     \
    indices.push_back(i2);                                                     \
    indices.push_back(i3);                                                     \
    indices.push_back(i1);                                                     \
    indices.push_back(i3);                                                     \
    indices.push_back(i4);                                                     \
  }

SphereMesh::~SphereMesh() {}
VertexArray *SphereMesh::GetVertexArray() {
  std::vector<float> vertices;
  std::vector<unsigned int> indices;

  int circumferenceTile = 10;
  int layerTile = 12;
  // constants
  const float PI = 3.1415926f;
  const float H_ANGLE = PI / 180 * 360;  // 72 degree = 360 / 5
  const float V_ANGLE = atanf(1.0f / 2); // elevation = 26.565 degree
  float radius = 1.0;

  int circCnt = (int)(circumferenceTile + 0.5f) * 3;
  if (circCnt < 4)
    circCnt = 4;
  int circCnt_2 = circCnt / 2;
  int layerCount = (int)(layerTile + 0.5f);
  if (layerCount < 2)
    layerCount = 2;

  for (int tbInx = 0; tbInx <= layerCount * 5; tbInx++) {
    float v = (1.0 - (float)tbInx / layerCount);
    float heightFac = sin((1.0 - 2.0 * tbInx / layerCount) * PI / 2.0);
    float cosUp = sqrt(1.0 - heightFac * heightFac);
    float z = heightFac;
    for (int i = 0; i <= circCnt_2; i++) {
      float u = (float)i / (float)circCnt_2;
      float angle = PI * u;
      float x = cos(angle) * cosUp;
      float y = sin(angle) * cosUp;
      vertices.push_back(x * radius);
      vertices.push_back(y * radius);
      vertices.push_back(z * radius);
    }
    for (int i = 0; i <= circCnt_2; i++) {
      float u = (float)i / (float)circCnt_2;
      float angle = PI * u + PI;
      float x = cos(angle) * cosUp;
      float y = sin(angle) * cosUp;
      vertices.push_back(x * radius);
      vertices.push_back(y * radius);
      vertices.push_back(z * radius);
    }
  }

  // Bottom cap
  int circSize_2 = circCnt_2 + 1;
  int circSize = circSize_2 * 2;
  for (int i = 0; i < circCnt_2; i++)
    AddFace(circSize + i, circSize + i + 1, i);
  for (int i = circCnt_2 + 1; i < 2 * circCnt_2 + 1; i++)
    AddFace(circSize + i, circSize + i + 1, i);

  // Center
  for (int tbInx = 1; tbInx < layerCount - 1; tbInx++) {
    int ringStart = tbInx * circSize;
    int nextRingStart = (tbInx + 1) * circSize;
    for (int i = 0; i < circCnt_2; i++)
      AddFaces(ringStart + i, nextRingStart + i, nextRingStart + i + 1,
               ringStart + i + 1);
    ringStart += circSize_2;
    nextRingStart += circSize_2;
    for (int i = 0; i < circCnt_2; i++)
      AddFaces(ringStart + i, nextRingStart + i, nextRingStart + i + 1,
               ringStart + i + 1);
  }

  // top
  int start = (layerCount - 1) * circSize;
  for (int i = 0; i < circCnt_2; i++)
    AddFace(start + i + 1, start + i, start + i + circSize);

  for (int i = circCnt_2 + 1; i < 2 * circCnt_2 + 1; i++)
    AddFace(start + i + 1, start + i, start + i + circSize);

  IndexBuffer *ib = IndexBuffer::Create(indices.data(), indices.size());

  VertexBuffer *vb = VertexBuffer::Create(vertices.data(), vertices.size());

  vb->SetLayout(BufferLayout({BufferElement(ShaderDataType::Float3, "cube")}));

  VertexArray *va = VertexArray::Create();
  va->Bind();
  va->AddVertexBuffer(vb);
  va->SetIndexBuffer(ib);

  return va;
}

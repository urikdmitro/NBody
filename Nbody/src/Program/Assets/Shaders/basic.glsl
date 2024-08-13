// basic shader

#type vertex
#version 330 core

layout (location = 0) in vec3 aPos;

uniform mat4 u_ViewProjection;
uniform mat4 u_transform;

void main()
{
  gl_Position = u_ViewProjection * u_transform * vec4(aPos, 1.0);
}

#type fragment
#version 330 core

out vec4 FragColor;


void main()
{
  FragColor = vec4(0.95f, 0.55f, 0.66f, 1.0f);
}

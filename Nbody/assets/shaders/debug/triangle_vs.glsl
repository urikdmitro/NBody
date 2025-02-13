// basic shader

#type vertex
#version 330 core

layout (location = 0) in vec3 aPos;

uniform mat4 u_ViewProjection;
uniform mat4 transform;

void main()
{
  gl_Position = u_ViewProjection * transform * vec4(aPos, 1.0);
}

#type fragment
#version 330 core

out vec4 FragColor;


void main()
{
  FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
}

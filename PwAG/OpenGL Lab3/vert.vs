#version 430 

uniform mat4 MVP;
out vec3 v_Color;

layout(location = 0) in vec3 v_Position;
layout(location = 1) in vec3 normals_vector;
layout(location = 2) in vec2 uvs_vector;
layout(location = 3) in vec3 colors_vector;

void main() {
  gl_Position = MVP * vec4(v_Position, 1.0);

  v_Color = colors_vector;
}
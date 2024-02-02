#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 color;

out vec3 Color;
uniform vec3 u_fragmentColor;
void main() {
  Color = vec3(u_fragmentColor.x, u_fragmentColor.y, u_fragmentColor.z);
   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
};

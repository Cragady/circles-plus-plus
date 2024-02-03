#version 460 core

out vec4 FragColor;
uniform vec3 u_fragmentColor;

void main()
{
   FragColor = vec4(u_fragmentColor, 1.0f);
};

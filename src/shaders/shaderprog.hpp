#ifndef SHADERPROG_HPP
#define SHADERPROG_HPP

#include <string>
#include <glm/vec3.hpp>

class ShaderProg {
public:
  ShaderProg();

  ~ShaderProg();

  void setFragmentColor(glm::vec3 t_color_vector);

  void attach(const char *fileName, unsigned int shaderType);

  void link();

  void use();

private:
  unsigned int m_pId;

  std::string readShaderFromFile(const char *fileName);
};

#endif

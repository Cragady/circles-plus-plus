#ifndef SHADERPROG_HPP
#define SHADERPROG_HPP

#include <string>
#include <glm/vec3.hpp>
#include <glad/glad.h>

class ShaderProg {
public:
  ShaderProg();

  ~ShaderProg();

  void setFragmentColor(glm::vec3 t_color_vector);

  GLuint getUniform(std::string location);

  void attach(const char *fileName, unsigned int shaderType);

  void link();

  void use();

  void setVSandFSLocations(std::string vs_name, std::string fs_name);

  GLuint getID();

private:
  unsigned int m_pId;

  std::string readShaderFromFile(const char *fileName);
};

#endif

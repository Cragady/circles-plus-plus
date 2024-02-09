#ifndef SHADERPROG_HPP
#define SHADERPROG_HPP

#include <string>
#include <glm/vec3.hpp>
#include <glad/glad.h>

class ShaderProg {
public:
  ShaderProg();

  ~ShaderProg();

  ShaderProg(const ShaderProg &other);
  ShaderProg(ShaderProg &&other);

  ShaderProg &operator=(ShaderProg &other);
  ShaderProg &operator=(ShaderProg &&other);

  friend void swap(ShaderProg &first, ShaderProg &second);

  void setFragmentColor(glm::vec3 t_color_vector);

  GLuint getUniform(std::string location);

  void attach(const char *fileName, unsigned int shaderType);

  void link();

  void use();

  void setVSandFSLocations(std::string vs_name, std::string fs_name);

  GLuint getID();

private:
  unsigned int m_pId = 0;

  std::string readShaderFromFile(const char *fileName);
};

void swap(ShaderProg &first, ShaderProg &second);

#endif

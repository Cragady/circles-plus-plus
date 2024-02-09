#include "shaderprog.hpp"
#include <fstream>
#include <glad/glad.h>
#include <iostream>
ShaderProg::ShaderProg() {
  // constructor

  m_pId = glCreateProgram();
}
ShaderProg::~ShaderProg() {
  // destructor
  if (m_pId)
    glDeleteProgram(m_pId);
}

ShaderProg::ShaderProg(const ShaderProg &other) : m_pId(other.m_pId) {
}

ShaderProg::ShaderProg(ShaderProg &&other) : ShaderProg() {
  swap(*this, other);
}

ShaderProg &ShaderProg::operator=(ShaderProg &other) {
  swap(*this, other);
  return *this;
}

ShaderProg &ShaderProg::operator=(ShaderProg &&other) {
  swap(*this, other);
  return *this;
}

void swap(ShaderProg &first, ShaderProg &second) {
  using std::swap;
  swap(first.m_pId, second.m_pId);
}

void ShaderProg::setVSandFSLocations(std::string vs_name, std::string fs_name) {
  if (vs_name.length() == 0) {
    std::cout << "Vertex Shader name invalid!" << std::endl;
    return;
  }

  std::string c_vs_name = vs_name + '\0';
  attach(&c_vs_name[0], GL_VERTEX_SHADER);

  if (fs_name.length() == 0) {
    std::cout << "Fragment Shader name invalid!" << std::endl;
    return;
  }

  std::string c_fs_name = fs_name + '\0';
  attach(&c_fs_name[0], GL_FRAGMENT_SHADER);
}

void ShaderProg::setFragmentColor(glm::vec3 t_color_vector) {
  GLuint location = glGetUniformLocation(m_pId, "u_fragmentColor");
  if (location >= 0)
    glUniform3fv(location, 1, &t_color_vector[0]);
};

GLuint ShaderProg::getUniform(std::string location) {
  std::string c_location = location + '\0';
  return glGetUniformLocation(m_pId, &location[0]);
}

void ShaderProg::link() {
  // links the shader object into program object
  glLinkProgram(m_pId);
  // check if it is linked
  int isLinked;
  char logMsg[512];
  glGetProgramiv(m_pId, GL_LINK_STATUS, &isLinked);
  if (!isLinked) {
    glGetProgramInfoLog(m_pId, 512, NULL, logMsg);
    std::cout << "Program Linking error: " << std::endl << logMsg << std::endl;
  }
}

void ShaderProg::use() { glUseProgram(m_pId); }

void ShaderProg::attach(const char *fileName, unsigned int shaderType) {
  // create a shader object
  unsigned int shaderId = glCreateShader(shaderType);
  // get shader code
  std::string srcCode = readShaderFromFile(fileName);
  // define shader code
  const char *chSrcCode = &srcCode[0];
  // glShaderSource(shaderId, 1, &chSrcCode, 0);
  glShaderSource(shaderId, 1, &chSrcCode, NULL);
  // compile the shader object
  glCompileShader(shaderId);
  // check if the compiling process works ok
  int isCompiled;
  char logMsg[512];
  glGetShaderiv(shaderId, GL_COMPILE_STATUS, &isCompiled);
  if (!isCompiled) {
    glGetShaderInfoLog(shaderId, 512, 0, logMsg);
    std::cout << "ShaderType: " << shaderType << std::endl
              << logMsg << std::endl;
  }
  // attach shader object to the program object
  glAttachShader(m_pId, shaderId);
  // after adding the shader object, we don't need it anymore
  glDeleteShader(shaderId);
}

std::string ShaderProg::readShaderFromFile(const char *fileName) {
  // reads the source code from the shader source file

  std::ifstream file(fileName);
  std::string stringData;
  if (file.is_open()) {
    char aChar;
    // read each character one by one
    while ((aChar = file.get()) != EOF) {
      stringData += aChar;
    }
    file.close();
  }
  return stringData;
}

GLuint ShaderProg::getID() {
  return m_pId;
}

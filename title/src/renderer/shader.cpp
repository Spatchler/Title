#include "renderer/shader.hpp"

using namespace Title;

void Shader::checkCompileErrors(GLuint pShader, std::string pType) {
  GLint success;
  GLchar infoLog[1024];
  if (pType != "PROGRAM") {
    glGetShaderiv(pShader, GL_COMPILE_STATUS, &success);
    if (!success) {
      glGetShaderInfoLog(pShader, 1024, NULL, infoLog);
      std::println("ERROR::SHADER_COMPILATION_ERROR of type: {0}\n{1}\n -- --------------------------------------------------- -- ", pType, infoLog);
    }
  }
  else {
    glGetProgramiv(pShader, GL_LINK_STATUS, &success);
    if (!success) {
      glGetProgramInfoLog(pShader, 1024, NULL, infoLog);
      std::println("ERROR::PROGRAM_LINKING_ERROR of type: {0}\n{1}\n -- --------------------------------------------------- -- ", pType, infoLog);
    }
  }
}

Shader::Shader(const char* pVertexPath, const char* pFragmentPath) {
  std::string vertexCode;
  std::string fragmentCode;
  std::ifstream vShaderFile;
  std::ifstream fShaderFile;

  vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

  try {
    // Read files
    vShaderFile.open(pVertexPath);
    fShaderFile.open(pFragmentPath);
    std::stringstream vShaderStream, fShaderStream;
    vShaderStream << vShaderFile.rdbuf();
    fShaderStream << fShaderFile.rdbuf();
    vShaderFile.close();
    fShaderFile.close();
    vertexCode = vShaderStream.str();
    fragmentCode = fShaderStream.str();
  }
  catch (std::ifstream::failure& e) {
    std::println("ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: {0}", e.what());
  }
  const char* vShaderCode = vertexCode.c_str();
  const char* fShaderCode = fragmentCode.c_str();

  // Compile
  uint vertex, fragment;
  // vertex shader
  vertex = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex, 1, &vShaderCode, NULL);
  glCompileShader(vertex);
  checkCompileErrors(vertex, "VERTEX");
  // fragment Shader
  fragment = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment, 1, &fShaderCode, NULL);
  glCompileShader(fragment);
  checkCompileErrors(fragment, "FRAGMENT");
  // shader Program
  mID = glCreateProgram();
  glAttachShader(mID, vertex);
  glAttachShader(mID, fragment);
  glLinkProgram(mID);
  checkCompileErrors(mID, "PROGRAM");
  // delete the shaders as they're linked into our program now and no longer necessary
  glDeleteShader(vertex);
  glDeleteShader(fragment);
}

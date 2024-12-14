#include "renderer/mesh.hpp"

using namespace Title;

Mesh::Mesh(std::size_t pBufferSize, const void* pData, bool pIsIndexed)
:mIsIndexed(pIsIndexed) {
  glGenVertexArrays(1, &mVAO);
  glGenBuffers(1, &mVBO);

  glBindVertexArray(mVAO);
  glBindBuffer(GL_ARRAY_BUFFER, mVBO);

  glBufferData(GL_ARRAY_BUFFER, pBufferSize, pData, GL_STATIC_DRAW);

  glBindVertexArray(0);
}

void Mesh::draw() {
  glBindVertexArray(mVAO);
  // if (mIndexed)
  //   glDrawElements(Gl_TRIANGLES, )
  glDrawArrays(GL_TRIANGLES, 0, 3);
  glBindVertexArray(0);
}

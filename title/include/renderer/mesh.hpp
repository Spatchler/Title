#pragma once

#include "rendererBase.hpp"

namespace Title {
  class Mesh {
  public:
    Mesh(std::size_t pBufferSize, const void* pData, bool pIsIndexed);

    template <typename T>
    void addVertexAttribute(uint pIndex, uint pSize, bool pIsNormalized, std::size_t pStride, const void* pPointer) {
      glBindVertexArray(mVAO);
      glBindBuffer(GL_ARRAY_BUFFER, mVBO);

      const char* type = typeid(T).name();
      if (*type == 'f') {
        glVertexAttribPointer(pIndex, pSize, GL_FLOAT, pIsNormalized, pStride, pPointer);
      }

      glEnableVertexAttribArray(pIndex);

      glBindVertexArray(0);
    }

    void draw();
  private:
    uint mVAO, mVBO;
    bool mIsIndexed;
  };
}

#include "title.hpp"

int main() {
  Title::Window& window = Title::Window::get();
  window.init("Window title");
  window.setClearColor(glm::vec4(0.2f, 0.3f, 0.3f, 1.0f));

  float vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
  };
  Title::Mesh testMesh(sizeof(vertices), &vertices[0], false);
  testMesh.addVertexAttribute<float>(0, 3, false, sizeof(float) * 3, (void*)0);

  Title::Shader testShader("sandbox/res/shaders/testShader.vs", "sandbox/res/shaders/testShader.fs");

  while (!window.shouldWindowClose()) {
    window.clear();

    // Render ---

    testShader.use();
    testMesh.draw();

    // Render ---

    window.swapBuffers();
    window.pollEvents();
  }

  return 0;
}

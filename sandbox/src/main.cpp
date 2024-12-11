#include "title.hpp"

int main() {
  Title::Window& window = Title::Window::get();
  window.init("Window title");
  window.setClearColor(glm::vec4(0.2f, 0.3f, 0.3f, 1.0f));

  while (!window.shouldWindowClose()) {
    window.clear();

    // Render ---

    // Render ---

    window.swapBuffers();
    window.pollEvents();
  }

  return 0;
}

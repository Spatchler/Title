#pragma once

#include "renderer/rendererBase.hpp"

void framebufferSizeCallback(GLFWwindow* pWindow, int pWidth, int pHeight);
void mouseCallback(GLFWwindow* pWindow, double pX, double pY);
void scrollCallback(GLFWwindow* pWindow, double pXoffset, double pYoffset);

namespace Title {
  class Window {
  public:
    Window(const Window&) = delete;
    static Window& get() { return instance; }

    void init(const char* pTitle);
    ~Window();

    void clear();
    void swapBuffers();
    void pollEvents();
    bool shouldWindowClose();
    void setViewportSize(glm::vec2 pSize);
    void updateMousePos(glm::vec2 pPos);

    void setClearColor(glm::vec4 pClearColor);
    glm::vec4 getClearColor();

    void setVSYNC(bool pVSYNC);
    bool getVSYNC();
  protected:
    Window() {};
    static Window instance;

    glm::vec4 mClearColor;
    glm::vec2 mSize;
    bool mVsync = true;
    bool mFirstMouse;
    bool mVSYNC;
    glm::vec2 mLastMousePos;
    GLFWwindow* mWindow = NULL;
  };
}

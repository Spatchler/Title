#include "renderer/window.hpp"

using namespace Title;

Window Window::instance;

void framebufferSizeCallback(GLFWwindow* pWindow, int pWidth, int pHeight) {
  Window::get().setViewportSize(glm::vec2(pWidth, pHeight));
}

void mouseCallback(GLFWwindow* pWindow, double pX, double pY) {
  Window::get().updateMousePos(glm::vec2(pX, pY));
}

void scrollCallback(GLFWwindow* pWindow, double pXoffset, double pYoffset) {
  glm::vec2 offset(pXoffset, pYoffset);
}

void Window::init(const char* pTitle) {
  // GLFW Init and configure
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef _MACOSX
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  // GLFW Window creation
  mSize.x = 720;
  mSize.y = 720;
  mWindow = glfwCreateWindow(mSize.x, mSize.y, pTitle, NULL, NULL);
  if (mWindow == NULL) {
    std::println("Failed to create GLFW window");
    glfwTerminate();
    return;
  }
  glfwMakeContextCurrent(mWindow);

  // Enable VSYNC by default
  glfwSwapInterval(0);

  // GLFW callbacks
  glfwSetFramebufferSizeCallback(mWindow, framebufferSizeCallback);
  glfwSetCursorPosCallback(mWindow, mouseCallback);
  glfwSetScrollCallback(mWindow, scrollCallback);

  // Capture mouse
  glfwSetInputMode(mWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

  // GLAD Load opengl function pointers
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    std::println("Failed to initialize GLAD");

  glEnable(GL_DEPTH_TEST);

  glLineWidth(2);
}

Window::~Window() {
  glfwDestroyWindow(mWindow);
}

void Window::clear() {
  glClearColor(mClearColor.x, mClearColor.y, mClearColor.z, mClearColor.w);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::swapBuffers() {
  glfwSwapBuffers(mWindow);
}

void Window::pollEvents() {
  glfwPollEvents();
}

bool Window::shouldWindowClose() {
  return glfwWindowShouldClose(mWindow);
}

void Window::setViewportSize(glm::vec2 pSize) {
  glViewport(0, 0, pSize.x, pSize.y);
  mSize = pSize;
}

void Window::updateMousePos(glm::vec2 pPos) {
  if (mFirstMouse) {
    mLastMousePos = pPos;
    mFirstMouse = false;
  }

  glm::vec2 offset(pPos.x - mLastMousePos.x, mLastMousePos.y - pPos.y);
  mLastMousePos = pPos;

  // Offset is the mouse pos to pass to camera
}

void Window::setClearColor(glm::vec4 pClearColor) {
  mClearColor = pClearColor;
  glClearColor(mClearColor.x, mClearColor.y, mClearColor.z, mClearColor.w);
}

glm::vec4 Window::getClearColor() {
  return mClearColor;
}

void Window::setVSYNC(bool pVSYNC) {
  mVSYNC = pVSYNC;
  if (mVSYNC)
    glfwSwapInterval(-1);
  else
    glfwSwapInterval(0);
}

bool Window::getVSYNC() {
  return mVSYNC;
}

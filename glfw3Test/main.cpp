#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <AntTweakBar.h>
#include <iostream>


void EventMouseButtonGLFW3(GLFWwindow* window, int button, int action, int mods) {
  if (TwEventMouseButtonGLFW(button, action)) return;
}
void EventMousePosGLFW3(GLFWwindow* window, double xpos, double ypos) {
  if (TwMouseMotion(int(xpos), int(ypos))) return;
}
void EventMouseWheelGLFW3(GLFWwindow* window, double xoffset, double yoffset) {
  if (TwEventMouseWheelGLFW(int(yoffset))) return;
}
void EventKeyGLFW3(GLFWwindow* window, int key, int scancode, int action, int mods) {
  if (TwEventKeyGLFW(key, action)) return;
}
void EventCharGLFW3(GLFWwindow* window, int codepoint) {
  if (TwEventCharGLFW(codepoint, GLFW_PRESS)) return;
}
void WindowSizeGLFW3(GLFWwindow* window, int width, int height) {
  TwWindowSize(width, height);
}


int main()
{
  if (!glfwInit()) {
    std::cerr << "Error initializing glfw...\n";
    exit(-1);
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

  GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL", nullptr, nullptr); // Windowed
  if (!window) {
    std::cerr << "Error creating window...\n";
    glfwTerminate();
    exit(-1);
  }
  glfwMakeContextCurrent(window);
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL); // can be GLFW_CURSOR_HIDDEN

  // Initialize AntTweakBar
  //TwInit(TW_OPENGL, NULL);
  TwInit(TW_OPENGL_CORE, NULL);

  // Create a tweak bar
  TwBar *bar = TwNewBar("TweakBar");
  TwWindowSize(800, 600);
  TwDefine(" GLOBAL help='This example shows how to integrate AntTweakBar with GLFW and OpenGL.' "); // Message added to the help bar.

  // Set GLFW event callbacks
  glfwSetWindowSizeCallback(window, (GLFWwindowposfun)WindowSizeGLFW3);
  glfwSetMouseButtonCallback(window, (GLFWmousebuttonfun)EventMouseButtonGLFW3);
  glfwSetCursorPosCallback(window, (GLFWcursorposfun)EventMousePosGLFW3);
  glfwSetScrollCallback(window, (GLFWscrollfun)EventMouseWheelGLFW3);
  glfwSetKeyCallback(window, (GLFWkeyfun)EventKeyGLFW3);
  glfwSetCharCallback(window, (GLFWcharfun)EventCharGLFW3);

  glewExperimental = GL_TRUE;
  if (glewInit() != GLEW_NO_ERROR) {
    std::cerr << "Error initializing GLEW...\n";
    glfwTerminate();
    exit(-1);
  }
  
  while (!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT);
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
      glfwSetWindowShouldClose(window, GL_TRUE);
    float time = (float)glfwGetTime();
    TwDraw();
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  TwTerminate();
  glfwTerminate();
  return 0;
}
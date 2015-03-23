#include <gl/rgGLObject.h>
#include <gl/rgGLCamera.h>
#include <gl/rgGLLight.h>
#include <gl/rgGLObject3D.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <AntTweakBar.h>

namespace rg {


class GLSphere : public GLObject3D {
 public:
  GLSphere(const std::string& Name, GLObject* Parent = nullptr)
      : GLObject3D(Name, SPHERE, Parent) {}
};
//------------------------------------------

class GLScene {
 public:
  GLScene() { Root = new GLObject("Root", GLObject::ROOT); }

  ~GLScene() { deleteObjects(); }

  void init() {
    auto MainCamera = new GLCamera("MainCamera", Root);
    add(MainCamera);
    auto L1 = new GLLight("Light_01", GLLight::DIRECTIONAL, Root);
    add(L1);
    
    auto O1 = new GLCuboid("Cube_01", Root);
    add(O1);
   
    auto O2 = new GLCuboid("Cube_02", Root);
    add(O2);
    O2->setParent(O1);
    auto O3 = new GLCuboid("Cube_03", Root);
    add(O3);
    auto O4 = new GLSphere("Sphere_01", O1);
  }

  void add(GLObject3D* O) {
    Objects3D[O->getName()] = O;
    Objects[O->getName()] = O;
  }

  void add(GLLight* O) {
    Lights[O->getName()] = O;
    Objects[O->getName()] = O;
  }

  void add(GLCamera* O) {
    Cameras[O->getName()] = O;
    Objects[O->getName()] = O;
  }

  void deleteObjects() {
    for (auto e : Objects) delete e.second;
  }

  void dump() {
    for (auto e : Objects) {
      std::cout << e.second->getName() << std::endl;
    }
  }

  void dumpTree(GLObject* Node, std::string& tab) {
    if (Node != nullptr) {
      std::cout << tab << Node->getName() << std::endl;
      for (auto e : Node->getChildren()) {
        dumpTree(e.second, tab + " ");
      }
    }
  }

  void dumpTree() {
    std::string tab = "";
    dumpTree(Root, tab);
  }

 private:
  GLObject* Root;
  std::map<std::string, GLCamera*> Cameras;
  std::map<std::string, GLLight*> Lights;
  std::map<std::string, GLObject3D*> Objects3D;
  std::map<std::string, GLObject*> Objects;
};
}

void EventMouseButtonGLFW3(GLFWwindow* window, int button, int action,
                           int mods) {
  if (TwEventMouseButtonGLFW(button, action)) return;
  //  if (World.EventMouseButton(button, action)) return;
}
void EventMousePosGLFW3(GLFWwindow* window, double xpos, double ypos) {
  if (TwMouseMotion(int(xpos), int(ypos))) return;
  // if (World.EventMousePos(xpos, ypos)) return;
}
void EventMouseWheelGLFW3(GLFWwindow* window, double xoffset, double yoffset) {
  if (TwEventMouseWheelGLFW(int(yoffset))) return;
  //  if (World.EventMouseWheel(yoffset)) return;
}
void EventKeyGLFW3(GLFWwindow* window, int key, int scancode, int action,
                   int mods) {
  if (TwEventKeyGLFW(key, action)) return;
  // if (World.EventKey(key, action)) return;
}
void EventCharGLFW3(GLFWwindow* window, int codepoint) {
  if (TwEventCharGLFW(codepoint, GLFW_PRESS)) return;
}
void WindowSizeGLFW3(GLFWwindow* window, int width, int height) {
  TwWindowSize(width, height);
}

void ErrorGLFW3(int r, const char* err) {
  std::cout << "Error GLFW3 " << r << " " << err << std::endl;
}

int main() {
  glfwSetErrorCallback((GLFWerrorfun)ErrorGLFW3);

  std::cout << "Initializating glfw3..\n";
  if (!glfwInit()) {
    std::cerr << "Error initializing glfw...\n";
    exit(-1);
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

  GLFWwindow* window =
      glfwCreateWindow(800, 600, "OpenGL", nullptr, nullptr);  // Windowed
  if (!window) {
    std::cerr << "Error creating window...\n";
    glfwTerminate();
    exit(-1);
  }
  glfwMakeContextCurrent(window);
  glfwSetInputMode(window, GLFW_CURSOR,
                   GLFW_CURSOR_NORMAL);  // can be GLFW_CURSOR_HIDDEN
  glfwSetWindowPos(window, 2300, 100);


  // Initialize AntTweakBar
  // TwInit(TW_OPENGL, NULL);
  TwInit(TW_OPENGL_CORE, NULL);

  // Create a tweak bar
  TwBar* bar = TwNewBar("TweakBar");
  TwWindowSize(800, 600);
  TwDefine(" GLOBAL help='This example shows how to integrate AntTweakBar with GLFW and OpenGL.' ");  // Message added to the help bar.
  TwAddSeparator(bar, NULL, "group='Parameters' ");
  // TwAddVarRW(bar, "speed", TW_TYPE_DOUBLE, &speed,
  //              " label='Rot speed' min=0 max=2 step=0.01 keyIncr=s
  // keyDecr = S
  // help='Rotation speed (turns/second)' ");

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
  
  rg::GLScene S;
  S.init();
  S.dumpTree();


  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  glEnable(GL_CULL_FACE);

  // glfwSwapInterval(300);
  //  World.init();
  float t0 = (float)glfwGetTime();
  while (!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
      glfwSetWindowShouldClose(window, GL_TRUE);
    float time = (float)glfwGetTime();
    // std::cout << "time = " << time - t0 << std::endl;
    t0 = time;
    //  World.render();
    TwDraw();
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  TwTerminate();
  glfwTerminate();
  return 0;
}
#include <iostream>

#include "core/application.h"
#include "core/inputhandler.h"
#include "core/keyboard.h"
#include "core/mouse.h"
#include "core/object.h"
#include "core/signal.h"
#include "core/timer.h"
#include "core/window.h"
#include "core/point.h"
#include "core/scenemanager.h"
#include "core/scene.h"
#include "core/camera.h"
#include "core/freecamera.h"
#include "core/item.h"
#include "items/cubeitem.h"

class FrameCounter : public Dee::Object {
public:
  FrameCounter() : __fps(0) {}
  
  DeeSlot printFps() {
    std::cout << "Fps: " << __fps << std::endl;
    __fps = 0;
  }
  
  DeeSlot beforeRender() {
    __fps += 1;
  }
  
private:
  int __fps;
};

int main(int argc, char** argv) {
  Dee::Application app(argc, argv);
  
  app.beforeRender.connect([=]() {
    const Dee::Keyboard* keyboard = Dee::Application::input()->keyboard();
    
    /* Quit application on Esc */
    if (keyboard->keyDown(Dee::Key::Esc)) {
      deeApp->quit();
    }
    
    /* Toggle fullscreen on Ctrl + F */
    static bool keyDown = false;
    
    if (keyboard->keyDown(Dee::Key::F) && keyboard->keyDown(Dee::Key::LCtrl)) {
      if (!keyDown) {
        deeApp->window()->setFullscreen(!deeApp->window()->fullscreen());
        keyDown = true;
      }
    } else if (keyboard->keyDown(Dee::Key::H) && keyboard->keyDown(Dee::Key::LCtrl)) {
      if (!keyDown) {
        deeApp->sceneManager()->activeScene()->setAntyaliasing(true);
      }
    } else {
      keyDown = false;
    }
  });
  
  Dee::FreeCamera camera;
  camera.setEye({0.0f, 0.0f, -1.0f});
  app.sceneManager()->activeScene()->setCamera(&camera);
  
  app.beforeRender.connect([=, &camera]() {
    const Dee::Keyboard* keyboard = Dee::Application::input()->keyboard();
    
    if (keyboard->keyDown(Dee::Key::A))
      camera.move({-0.01f, 0.0f, 0.0f});
    
    if (keyboard->keyDown(Dee::Key::D))
      camera.move({0.01f, 0.0f, 0.0f});
    
    if (keyboard->keyDown(Dee::Key::S))
      camera.move({0.0f, 0.0f, -0.01f});
    
    if (keyboard->keyDown(Dee::Key::W))
      camera.move({0.0f, 0.0f, 0.01f});
    
    const Dee::Mouse* mouse = Dee::Application::input()->mouse();
    camera.rotate(mouse->motion());
  });
  
  Dee::CubeItem item;
  
  std::cout << sizeof(Dee::Vertex) << std::endl;
  
  app.sceneManager()->activeScene()->addRenderable(&item);
  
  FrameCounter counter;
  app.beforeRender.connect(&counter, &FrameCounter::beforeRender);
  Dee::Timer timer(1000);
  timer.timeout.connect(&counter, &FrameCounter::printFps);
  timer.start();
  
  Dee::Timer timer2(10);
  timer2.timeout.connect([=, &item]() {
    item.rotate(0.5f, Dee::Z);
    item.translate({ 0.0f, 0.01f, 0.0f });
  });
  timer2.start();
  
  return app.run();
}
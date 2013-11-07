#include <iostream>

#include "core/application.h"
#include "core/inputhandler.h"
#include "core/keyboard.h"
#include "core/object.h"
#include "core/signal.h"
#include "core/timer.h"
#include "core/window.h"
#include "core/scenemanager.h"
#include "core/scene.h"
#include "core/camera.h"
#include "core/freecamera.h"
#include "core/item.h"

class FrameCounter : public Dee::Object {
public:
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
  app.window()->setFullscreen(true);
  
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
    } else {
      keyDown = false;
    }
  });
  
  Dee::FreeCamera camera;
  camera.setEye({0.0f, 0.0f, -1.0f});
  app.sceneManager()->activeScene()->setCamera(&camera);
  
  app.beforeRender.connect([=, &camera]() {
    const Dee::Keyboard* keyboard = Dee::Application::input()->keyboard();
    
    if (keyboard->keyDown(Dee::Key::Left))
      camera.move({0.01f, 0.0f, 0.0f});
    
    if (keyboard->keyDown(Dee::Key::Right))
      camera.move({-0.01f, 0.0f, 0.0f});
    
    if (keyboard->keyDown(Dee::Key::Up))
      camera.move({0.0f, 0.01f, 0.0f});
    
    if (keyboard->keyDown(Dee::Key::Down))
      camera.move({0.0f, -0.01f, 0.0f});
    
    if (keyboard->keyDown(Dee::Key::Minus))
      camera.move({0.0f, 0.0f, -0.1f});
    
    if (keyboard->keyDown(Dee::Key::Equal))
      camera.move({0.0f, 0.0f, 0.1f});
  });
  
  Dee::Item item;
  app.sceneManager()->activeScene()->addRenderable(&item);
  
  FrameCounter counter;
  app.beforeRender.connect(&counter, &FrameCounter::beforeRender);
  Dee::Timer timer(1000);
  timer.timeout.connect(&counter, &FrameCounter::printFps);
  timer.start();
  
  return app.run();
}

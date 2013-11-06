#include <iostream>

#include "core/application.h"
#include "core/inputhandler.h"
#include "core/keyboard.h"
#include "core/object.h"
#include "core/signal.h"
#include "core/timer.h"
#include <core/window.h>

class Listener : public Dee::Object {
public:
  DeeSlot timeout() {
    static int counter = 0;
    counter += 1;
    
    std::cout << "Timeout no. " << counter << std::endl;
    
    if (counter == 5)
      deeApp->quit();
  }
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
        std::cout << "Switching fullscreen..." << std::endl;
        deeApp->window()->setFullscreen(!deeApp->window()->fullscreen());
        keyDown = true;
      }
    } else {
      keyDown = false;
    }
  });
  
  Listener listener;
  
  Dee::Timer timer;
  timer.timeout.connect(&listener, &Listener::timeout);
  timer.setTimeout(1000);
  
  timer.start();
  return app.run();
}

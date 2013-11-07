#include <iostream>

#include "core/application.h"
#include "core/inputhandler.h"
#include "core/keyboard.h"
#include "core/object.h"
#include "core/signal.h"
#include "core/timer.h"
#include "core/window.h"

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
  
  return app.run();
}

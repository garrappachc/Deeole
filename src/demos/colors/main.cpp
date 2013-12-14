#include <iostream>
#include <fstream>
#include <sstream>

#include "core/application.h"
#include "core/color.h"
#include "core/cursor.h"
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

class InputData {
public:
  InputData(const std::string& fileName) {
    __fromFile(fileName);
    __findMaxMin();
  }
    
private:
  void __fromFile(const std::string& fileName) {
    std::ifstream f(fileName);
    while (!f.eof()) {
      std::string buffer;
      std::getline(f, buffer);
      std::istringstream line(buffer);
      
      float x, y, data;
      line >> x >> y >> data;
      
      __x.push_back(x);
      __y.push_back(y);
      __data.push_back(data);    std::cout << "Plik: : " << fileName;
    }
        
            f.close();
            
            std::cout << "Danych: " << __x.size() << std::endl;
  }
    
      void __findMaxMin() {
        __max = 0.0f;
        __min = __data[0];
        for (float d: __data) {
          if (__max < d)
            __max = d;
          if (__min > d)
            __min = d;
        }
      }
        
          void __normalize() {
            for (float& d: __data) {
              d /= __max;
            }
          }
            
              std::vector<float> __x, __y, __data;
              float __max, __min;
              
};

int main(int argc, char** argv) {
  Dee::Application app(argc, argv);
  if (!app.hasArgument("file")) {
    std::cout << "Usage: " << argv[0] << " --file <file name>" << std::endl;
    return 1;
  }
    
      InputData input(app.argumentValue("file"));
      
      app.cursor()->hide();
      
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
      camera.setEye({0.0f, 0.5f, 10.0f});
      camera.setLookAt({0.0f, 0.0, -1.0f});
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
        
        int x = deeApp->window()->width() / 2;
        int y = deeApp->window()->height() / 2;
        
        deeApp->cursor()->setPosition(x, y);
        
        //     std::cout << "LookAt: " << camera.lookAt() << std::endl;
      });
      
      return app.run();
}
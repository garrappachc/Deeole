#include <iostream>

#include "core/application.h"
#include "core/eventful.h"
#include "core/signal.h"
#include "core/timer.h"

class Listener : public Dee::Eventful {
public:
  DeeSlot timeout() {
    static int counter = 0;
    
    std::cout << "Timeout!" << std::endl;
    
    counter += 1;
    if (counter == 5)
      deeApp->quit();
  }
};

int main(int argc, char** argv) {
  Dee::Application app(argc, argv);
  
  Listener listener;
  
  Dee::Timer timer;
  timer.timeout.connect(&listener, &Listener::timeout);
  timer.timeout.connect([=]() {
    std::cout << "Indeed, timeout." << std::endl;
  });
  timer.setTimeout(1000);
  
  timer.start();
  return app.run();
}

#include <iostream>
#include "App.hpp"
#include "shared.hpp"
#include "ComponentA.hpp"

class AppManager : public App {
public:
    AppManager() : App("AppManager") {}

    bool init() override {
        std::cout << "[" << getName() << "] init()\n";
        return true;
    }

    void loop() override {
        std::cout << "[" << getName() << "] shared:    "
                  << getSharedMessage() << "\n"
                  << "[" << getName() << "] component: "
                  << getComponentAMessage() << "\n";
        // For demo, just run once:
        stop();
    }

    void cleanup() override {
        std::cout << "[" << getName() << "] cleanup()\n";
    }
};

int main(int argc, char* argv[]) {
    AppManager app;
    app.setLoopInterval(std::chrono::milliseconds(500)); // half‐second loop
    app.run();
    return 0;
}

#include "App.hpp"
#include <iostream>

App::App(const std::string& name)
  : name(name)
{}

App::~App() = default;

void App::run() {
    if (!init()) {
        std::cerr << "App \"" << name << "\" failed to initialize.\n";
        return;
    }
    running = true;
    std::cout << "=== [" << name << "] Starting main loop ===\n";
    while (running) {
        loop();
        std::this_thread::sleep_for(loopInterval);
    }
    cleanup();
    std::cout << "=== [" << name << "] Exited main loop ===\n";
}

void App::stop() {
    running = false;
}

void App::setLoopInterval(std::chrono::milliseconds interval) {
    loopInterval = interval;
}

const std::string& App::getName() const {
    return name;
}

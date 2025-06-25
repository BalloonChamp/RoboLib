#include "MainComponent.h"
#include <iostream>

MainComponent::MainComponent() : Component("main") {}

void MainComponent::register_component(std::unique_ptr<Component> c) {
    components_.push_back(std::move(c));
}

void MainComponent::start() {
    std::cout << "[main] starting registered components" << std::endl;
    for (auto& c : components_) {
        c->start();
    }
}

void MainComponent::stop() {
    for (auto& c : components_) {
        c->stop();
    }
    std::cout << "[main] stopped" << std::endl;
}

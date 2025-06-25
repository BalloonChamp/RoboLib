#ifndef MAIN_COMPONENT_H
#define MAIN_COMPONENT_H

#include "Component.h"
#include <vector>
#include <memory>

class MainComponent : public Component {
public:
    MainComponent();
    void register_component(std::unique_ptr<Component> c);
    void start() override;
    void stop() override;

private:
    std::vector<std::unique_ptr<Component>> components_;
};

#endif // MAIN_COMPONENT_H

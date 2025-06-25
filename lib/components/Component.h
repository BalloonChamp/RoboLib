#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>

class Component {
public:
    Component(std::string name) : name_(std::move(name)) {}
    virtual ~Component() = default;

    const std::string& name() const { return name_; }

    virtual void start() = 0;
    virtual void stop() = 0;

protected:
    std::string name_;
};

#endif // COMPONENT_H

#ifndef DATABASE_COMPONENT_H
#define DATABASE_COMPONENT_H

#include "Component.h"

class DatabaseComponent : public Component {
public:
    DatabaseComponent();
    void start() override;
    void stop() override;

private:
    pid_t pid_{-1};
};

#endif // DATABASE_COMPONENT_H

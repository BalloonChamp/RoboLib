#ifndef SCHEDULER_COMPONENT_H
#define SCHEDULER_COMPONENT_H

#include "Component.h"
#include <sys/types.h>

class SchedulerComponent : public Component {
public:
    SchedulerComponent();
    void start() override;
    void stop() override;

private:
    pid_t pid_{-1};
    void loop();
};

#endif // SCHEDULER_COMPONENT_H

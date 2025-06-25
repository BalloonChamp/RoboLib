#include "components/Component.h"
#include "hooks/GenericHook.h"
#include <vector>

// Simple component that could provide simulated data
class SimComponent : public Component {
public:
    SimComponent(Database& db) : Component("sim", db) {}
    void run() override {}
};

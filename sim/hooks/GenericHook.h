#include <string>
// Base class for environment hooks
class GenericHook {
public:
    virtual ~GenericHook() = default;
    virtual std::string read() { return {}; }
};

#include "ComponentA.hpp"
#include "shared.hpp"

std::string getComponentAMessage() {
    // Call into the shared lib for part of our behavior
    return "ComponentA forwarding: " + getSharedMessage();
}

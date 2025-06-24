#pragma once
#include "robotlib/base_component.h"
#include "robotlib/database_client.h"
#include <vector>
#include <string>

class Scheduler : public BaseComponent {
public:
    Scheduler(const std::vector<std::string>& sequence,
              int dbPort = 6000);
    void run() override;
private:
    std::vector<std::string> m_sequence;
    int m_dbPort;
};

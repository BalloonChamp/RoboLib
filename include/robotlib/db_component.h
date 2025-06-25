#pragma once
#include "robotlib/base_component.h"
#include "robotlib/database_client.h"
#include <string>
#include "robotlib/data_packet.h"

class DbComponent : public BaseComponent {
public:
    DbComponent(const std::string& name, int dbPort = 6000);
    void run() override;
protected:
    virtual std::string handleCommand(const std::string& cmd) = 0;
    virtual void sendTelemetry(DatabaseClient& db) {}
private:
    std::string m_name;
    int m_dbPort;
};

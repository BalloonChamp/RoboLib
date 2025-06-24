#pragma once
#include "robotlib/db_component.h"

class DbTouchSensor : public DbComponent {
public:
    DbTouchSensor(const std::string& name, int dbPort = 6000);
protected:
    std::string handleCommand(const std::string& cmd) override;
    void sendTelemetry(DatabaseClient& db) override;
private:
    bool m_pressed;
};

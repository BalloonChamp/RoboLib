#pragma once
#include "robotlib/db_component.h"
#include "robotlib/data_packet.h"

class DbMotor : public DbComponent {
public:
    DbMotor(const std::string& name, int id, int dbPort = 6000);
protected:
    std::string handleCommand(const std::string& cmd) override;
    void sendTelemetry(DatabaseClient& db) override;
private:
    int m_id;
    int m_position;
    DataPacket m_posPacket;
};

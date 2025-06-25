#ifndef DATABASE_CLIENT_H
#define DATABASE_CLIENT_H

#include <string>
#include <optional>
#include <hiredis/hiredis.h>

// Thin wrapper around hiredis for simple GET/SET commands.
class DatabaseClient {
public:
    static DatabaseClient& instance();

    void connect(const char* host = "127.0.0.1", int port = 6379);

    void set(const std::string& key, const std::string& value);
    std::optional<std::string> get(const std::string& key);

    ~DatabaseClient();

private:
    DatabaseClient() = default;
    redisContext* ctx_{nullptr};
};

#endif // DATABASE_CLIENT_H

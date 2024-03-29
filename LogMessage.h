#pragma once
#include <string>

enum Type{ Warning, Error, FatalError, Unknown};

class LogMessage {
public:
    LogMessage(const Type type, const std::string& message);
    Type type() const;
    const std::string& message() const;
private:
    Type type_;
    std::string message_;
};

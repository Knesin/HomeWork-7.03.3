#include "LogMessage.h"

LogMessage::LogMessage(const Type type, const std::string& message) :type_(type), message_(message) {};

Type LogMessage::type() const {
	return type_;
}

const std::string& LogMessage::message() const {
	return message_;
}
#pragma once
#include <memory>
#include <stdexcept>
#include <iostream>
#include <fstream>
#include "LogMessage.h"

class LogHandler // обработчик
{
public:
	explicit LogHandler(std::unique_ptr<LogHandler> next) :next_(std::move(next)) {};
	virtual ~LogHandler() = default;
	void reciveLog(const LogMessage& msg);
private:
	std::unique_ptr<LogHandler> next_;
	virtual bool handleLog(const LogMessage& msg) = 0;
};

class LogFatalErrorHandler : public LogHandler {
public:
	using LogHandler::LogHandler;
private:
	bool handleLog(const LogMessage& msg) override {
		if (msg.type() != Type::FatalError) {
			return false;
		}
		throw std::runtime_error(msg.message());
		return true;
	}
};

class LogErrorHandler : public LogHandler {
public:
	using LogHandler::LogHandler;
private:
	bool handleLog(const LogMessage& msg) override {
		if (msg.type() != Type::Error) {
			return false;
		}
		std::ofstream f("Log.txt", std::ios::app);
		f << "Error: " << msg.message() << std::endl;
		f.close();
		return true;
	}
};

class LogWarningHandler : public LogHandler {
public:
	using LogHandler::LogHandler;
private:
	bool handleLog(const LogMessage& msg) override {
		if (msg.type() != Type::Warning) {
			return false;
		}
		std::cout << "Warning: " << msg.message() << std::endl;
		return true;
	}
};
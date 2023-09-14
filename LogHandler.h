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
	bool handleLog(const LogMessage& msg) override;
};

class LogErrorHandler : public LogHandler {
public:
	using LogHandler::LogHandler;
private:
	bool handleLog(const LogMessage& msg) override;
};

class LogWarningHandler : public LogHandler {
public:
	using LogHandler::LogHandler;
private:
	bool handleLog(const LogMessage& msg) override;
};
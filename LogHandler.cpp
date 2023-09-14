#include "LogHandler.h"

void LogHandler::reciveLog(const LogMessage& msg) {
	if (handleLog(msg)) {
		return;
	}
	if(!next_) { // если нет потомка
		throw std::runtime_error("Unknown Error: " + msg.message()); //Сообщение должно быть обработано
	};
	next_->reciveLog(msg);
}

bool LogFatalErrorHandler::handleLog(const LogMessage& msg) {
	if (msg.type() != Type::FatalError) {
		return false;
	}
	throw std::runtime_error("Fatal Error: " + msg.message());
	return true;
}

bool LogErrorHandler::handleLog(const LogMessage& msg) {
	if (msg.type() != Type::Error) {
		return false;
	}
	std::ofstream f("Log.txt", std::ios::app);
	f << "Error: " << msg.message() << std::endl;
	f.close();
	return true;
}

bool LogWarningHandler::handleLog(const LogMessage& msg) {
	if (msg.type() != Type::Warning) {
		return false;
	}
	std::cout << "Warning: " << msg.message() << std::endl;
	return true;
}
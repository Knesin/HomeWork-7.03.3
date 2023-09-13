#include "LogHandler.h"

void LogHandler::reciveLog(const LogMessage& msg) {
	if (handleLog(msg)) {
		return;
	}
	if(!next_) {
		throw std::runtime_error("Unknown Error: Message should be handled!"); //Сообщение должно быть обработано
	};
	next_->reciveLog(msg);
}
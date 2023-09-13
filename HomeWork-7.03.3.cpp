#include <iostream>
#include <memory>
#include "LogHandler.h"

int main()
{
    auto fatal_error_handler = std::make_unique<LogFatalErrorHandler>(nullptr);
    auto error_handler = std::make_unique<LogErrorHandler>(std::move(fatal_error_handler));
    auto warning_handler = std::make_unique<LogWarningHandler>(std::move(error_handler));
    
    

    try {
        warning_handler->reciveLog(LogMessage(Type::Warning, "123"));
        warning_handler->reciveLog(LogMessage(Type::Unknown, "UUUnnnkkk"));
        warning_handler->reciveLog(LogMessage(Type::Error, "3212"));
        warning_handler->reciveLog(LogMessage(Type::FatalError, "FFFEEE"));

    }
    catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}
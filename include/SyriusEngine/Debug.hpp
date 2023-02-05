#pragma once

#include <iostream>
#include "Include.hpp"

namespace Syrius{

    typedef enum SR_MESSAGE_SOURCE{
        SR_MESSAGE_GENERAL      = 0x00,
        SR_MESSAGE_SYRIUS_CORE  = 0x01,
        SR_MESSAGE_RENDERER     = 0x02,
        SR_MESSAGE_ECS          = 0x03
    } SR_MESSAGE_SOURCE;

    typedef enum SR_MESSAGE_SEVERITY{
        SR_MESSAGE_SEVERITY_INFO    = 0x00,
        SR_MESSAGE_SEVERITY_LOW     = 0x01,      // mostly used for messages that are not important
        SR_MESSAGE_SEVERITY_MEDIUM  = 0x02,      // used for messages that are important, but not critical
        SR_MESSAGE_SEVERITY_HIGH    = 0x03,      // used for messages that are critical and (usually) results in program termination
        SR_MESSAGE_PRECONDITION     = 0x04,
        SR_MESSAGE_POSTCONDITION    = 0x05
    } SR_MESSAGE_SEVERITY;

    struct SR_API SyriusMessage{
        SR_MESSAGE_SEVERITY severity;
        SR_MESSAGE_SOURCE source;
        std::string file;
        std::string function;
        uint32 line;
        std::string message;
    };

    typedef void(*debugMessageFunc)(const SyriusMessage&);

    void SR_API defaultMessageHandler(const SyriusMessage& msg);

    std::string SR_API messageSourceToString(SR_MESSAGE_SOURCE source);

    std::string SR_API messageSeverityToString(SR_MESSAGE_SEVERITY severity);

    class MessageHandler{
    public:
        static void init();

        static void handleSyriusCoreMessage(const Message& msg);

        template<typename... Args>
        static void pushMessage(const std::string& message, SR_MESSAGE_SOURCE source, SR_MESSAGE_SEVERITY severity, const std::string& file, const std::string& function, uint32 line, Args... args){
            Size formatSize = std::snprintf(nullptr, 0, message.c_str(), args...);
            std::vector<byte> formatBuffer(formatSize + 1);
            std::snprintf(reinterpret_cast<char*>(formatBuffer.data()), formatSize + 1, message.c_str(), args...);

            SyriusMessage msg;
            msg.severity = severity ;
            msg.source = source;
            msg.function = function;
            msg.file = file;
            msg.line = line;
            msg.message = std::string(reinterpret_cast<char*>(formatBuffer.data()));

            m_Func(msg);
        }


    private:
        static debugMessageFunc m_Func;
    };

}

#define SR_MESSAGE_INFO(source, message, ...) \
    Syrius::MessageHandler::pushMessage(message, source, Syrius::SR_MESSAGE_SEVERITY::SR_MESSAGE_SEVERITY_INFO, SR_CORE_FILE, SR_CORE_FUNC, SR_CORE_LINE, ##__VA_ARGS__);

#define SR_MESSAGE_WARNING(source, message, ...) \
    Syrius::MessageHandler::pushMessage(message, source, Syrius::SR_MESSAGE_SEVERITY::SR_MESSAGE_SEVERITY_MEIDUM, SR_CORE_FILE, SR_CORE_FUNC, SR_CORE_LINE, ##__VA_ARGS__);

#define SR_MESSAGE_EXCEPTION(source, message, ...) \
    Syrius::MessageHandler::pushMessage(message, source, Syrius::SR_MESSAGE_SEVERITY::SR_MESSAGE_SEVERITY_HIGH, SR_CORE_FILE, SR_CORE_FUNC, SR_CORE_LINE, ##__VA_ARGS__);

#define SR_PRECONDITION(condition, source, message, ...) \
    if (!(condition)){Syrius::MessageHandler::pushMessage(message, source, Syrius::SR_MESSAGE_SEVERITY::SR_MESSAGE_PRECONDITION, SR_CORE_FILE, SR_CORE_FUNC, SR_CORE_LINE, ##__VA_ARGS__);}

#define SR_POSTCONDITION(condition, source, message, ...) \
    if (!(condition)){Syrius::MessageHandler::pushMessage(message, source, Syrius::SR_MESSAGE_SEVERITY::SR_MESSAGE_POSTCONDITION, SR_CORE_FILE, SR_CORE_FUNC, SR_CORE_LINE, ##__VA_ARGS__);}

#define SR_THROW_EXC_ON_CONDITION(condition, source, message, ...) \
    if (!(condition)){Syrius::MessageHandler::pushMessage(message, source, Syrius::SR_MESSAGE_SEVERITY::SR_MESSAGE_SEVERITY_HIGH, SR_CORE_FILE, SR_CORE_FUNC, SR_CORE_LINE, ##__VA_ARGS__);}


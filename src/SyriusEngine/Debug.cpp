#include "../../include/SyriusEngine/Debug.hpp"

namespace Syrius{

    void defaultMessageHandler(const SyriusMessage& msg){
        std::string message = "[Syrius: " + msg.function + "]: severity = " + messageSeverityToString(msg.severity) + ", type = " +
                              messageSourceToString(msg.source) + "\n";
        message += "File = " + msg.file + ", line = " + std::to_string(msg.line) + "\n";
        message += "Message = " + msg.message + "\n";
        std::cerr << message;
        std::cerr << "\n\n--------------------------------------------------------------------------------\n";
    }

    std::string SR_API messageSourceToString(SR_MESSAGE_SOURCE source){
        switch (source) {
            case SR_MESSAGE:                return "MESSAGE";
            case SR_MESSAGE_SYRIUS_CORE:    return "SYRIUS_CORE";
            case SR_MESSAGE_RENDERER:       return "RENDERER";
            case SR_MESSAGE_ECS:            return "ECS";
        }
    }

    std::string SR_API messageSeverityToString(SR_MESSAGE_SEVERITY severity){
        switch (severity) {
            case SR_MESSAGE_SEVERITY_INFO:  return "INFO";
            case SR_MESSAGE_SEVERITY_LOW:   return "LOW";
            case SR_MESSAGE_SEVERITY_MEDIUM:return "MEDIUM";
            case SR_MESSAGE_SEVERITY_HIGH:  return "HIGH";
            case SR_MESSAGE_PRECONDITION:   return "PRECONDITION";
            case SR_MESSAGE_POSTCONDITION:  return "POSTCONDITION";
        }
    }

    debugMessageFunc MessageHandler::m_Func = defaultMessageHandler;

    void MessageHandler::init() {
        setDebugMessageCallback(MessageHandler::handleSyriusCoreMessage);
    }

    void MessageHandler::handleSyriusCoreMessage(const Message &msg) {
        SyriusMessage srMsg;
        srMsg.severity = static_cast<SR_MESSAGE_SEVERITY>(msg.severity);
        srMsg.file = msg.file;
        srMsg.function = msg.function;
        srMsg.line = msg.line;
        srMsg.source = SR_MESSAGE_SYRIUS_CORE;
        srMsg.message = msg.message;

        m_Func(srMsg);
    }

}



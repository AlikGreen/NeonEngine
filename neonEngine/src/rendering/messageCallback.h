#pragma once
#include <nvrhi/nvrhi.h>

class MessageCallback : public nvrhi::IMessageCallback
{
public:
    void message(nvrhi::MessageSeverity severity, const char* messageText) override
    {

    }
};
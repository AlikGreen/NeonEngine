#include "assert.h"

namespace Neon
{
    AssertAction Assert::assertAction = AssertAction::LogAndAbort;


    void Assert::check(const bool condition, const std::string &message, const std::source_location &location)
    {
        if(condition) return;
        const std::string fullMessage = "ASSERTION FAILED: " + message + "\n" +
                                        "  Function:  " + location.function_name() + "\n" +
                                        "  File:      " + location.file_name() + "\n" +
                                        "  Line:      " + std::to_string(location.line());

        switch (assertAction)
        {
            case AssertAction::LogAndThrow:
                throw std::runtime_error(fullMessage);
            case AssertAction::LogAndAbort:
                std::abort();
            case AssertAction::LogOnly:
                    break;
        }
    }
}

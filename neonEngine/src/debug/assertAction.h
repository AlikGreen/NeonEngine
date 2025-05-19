#pragma once

enum class AssertAction
{
    // LOG_AND_BREAK,
    LogAndThrow,
    LogAndAbort,
    LogOnly
};
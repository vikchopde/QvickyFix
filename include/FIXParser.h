#ifndef QVICKYFIX_FIXPARSER_H
#define QVICKYFIX_FIXPARSER_H

#include <iostream>
#include <memory>
#include <vector>
#include "FIXFieldStore.h"
#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <string>

namespace QvickyFix
{
    class FIXParser
    {
    public:
        using Tokens = std::vector<std::string>;

        FIXParser(const std::string message)
                : msg_(std::move(message))
        {
        }

        Tokens operator()()
        {
            std::vector<std::string> tokens;
            boost::split(tokens, msg_, boost::is_any_of("|^;\u0001"));
            return tokens;
        }

    private:
        std::string msg_;
        std::vector<std::string> fieldTokens_;
    };
}


#endif //QVICKYFIX_FIXPARSER_H

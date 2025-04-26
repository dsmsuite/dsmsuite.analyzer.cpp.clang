#pragma once

#include <string>

class ICodeAnalyzer {
public:
    virtual ~ICodeAnalyzer() = default;
    virtual bool analyze(const std::string& compilationDbPath) = 0;
};

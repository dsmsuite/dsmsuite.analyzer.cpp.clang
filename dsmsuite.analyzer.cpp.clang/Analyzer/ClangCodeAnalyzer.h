#pragma once

#include "ICodeAnalyzer.h"
#include "IGraphRepository.h"

class ClangCodeAnalyzer : public ICodeAnalyzer {
public:
    explicit ClangCodeAnalyzer(std::shared_ptr<IGraphRepository> repo);
    bool analyze(const std::string& compilationDbPath) override;

private:
    std::shared_ptr<IGraphRepository> repo_;
};

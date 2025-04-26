#pragma once
#include <clang/Frontend/FrontendAction.h>
#include "NodeEmitter.h"

class DependencyFrontendAction : public clang::ASTFrontendAction {
public:
    explicit DependencyFrontendAction(NodeEmitter& emitter);
    std::unique_ptr<clang::ASTConsumer> CreateASTConsumer(
        clang::CompilerInstance& CI, llvm::StringRef file) override;

private:
    NodeEmitter& emitter_;
};

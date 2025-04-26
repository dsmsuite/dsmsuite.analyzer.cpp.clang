#include "DependencyFrontendAction.h"
#include "DependencyVisitor.h"
#include <clang/AST/ASTConsumer.h>

class VisitorConsumer : public clang::ASTConsumer {
public:
    VisitorConsumer(NodeEmitter& emitter) : visitor_(emitter) {}
    void HandleTranslationUnit(clang::ASTContext& Context) override {
        visitor_.TraverseDecl(Context.getTranslationUnitDecl());
    }
private:
    DependencyVisitor visitor_;
};

DependencyFrontendAction::DependencyFrontendAction(NodeEmitter& emitter)
    : emitter_(emitter) {}

std::unique_ptr<clang::ASTConsumer> DependencyFrontendAction::CreateASTConsumer(
    clang::CompilerInstance& CI, llvm::StringRef file) {
    return std::make_unique<VisitorConsumer>(emitter_);
}

// Inside a FrontendAction, in BeginSourceFileAction():
// 
// ?????

CI.getPreprocessor().addPPCallbacks(
    std::make_unique<IncludeTracker>(emitter_, CI.getSourceManager()));

#include "ClangCodeAnalyzer.h"
#include "DependencyVisitor.h"
#include "NodeEmitter.h"

#include <clang/Tooling/Tooling.h>
#include <clang/Tooling/CommonOptionsParser.h>
#include <clang/Tooling/CompilationDatabase.h>
#include <clang/Tooling/AllTUsExecution.h>
#include <clang/Frontend/FrontendActions.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Frontend/FrontendPluginRegistry.h>
#include <clang/Tooling/Tooling.h>

using namespace clang;
using namespace clang::tooling;

ClangCodeAnalyzer::ClangCodeAnalyzer(std::shared_ptr<IGraphRepository> repo)
    : repo_(std::move(repo)) {}

bool ClangCodeAnalyzer::analyze(const std::string& compilationDbPath) {
    std::string errorMsg;
    std::unique_ptr<CompilationDatabase> Compilations =
        CompilationDatabase::loadFromDirectory(compilationDbPath, errorMsg);

    if (!Compilations) {
        llvm::errs() << "Failed to load compilation database: " << errorMsg << "\n";
        return false;
    }

    ClangTool Tool(*Compilations, Compilations->getAllFiles());

    NodeEmitter emitter(repo_);
    DependencyVisitor::registerEmitter(&emitter);

    return Tool.run(newFrontendActionFactory<DependencyVisitor>().get()) == 0;
}

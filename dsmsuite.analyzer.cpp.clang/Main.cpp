#include <clang/Tooling/CommonOptionsParser.h>
#include <clang/Tooling/Tooling.h>
#include <clang/Frontend/FrontendActions.h>
#include "NodeEmitter.h"
#include "DependencyFrontendAction.h"
#include "GraphRepositorySqlite.h"

using namespace clang::tooling;

int main(int argc, const char **argv) {
    llvm::cl::OptionCategory ToolCategory("dep-analyzer");
    CommonOptionsParser OptionsParser(argc, argv, ToolCategory);
    ClangTool Tool(OptionsParser.getCompilations(), OptionsParser.getSourcePathList());

    auto repo = std::make_shared<GraphRepositorySqlite>("deps.db");
    NodeEmitter emitter(repo);
    auto factory = clang::tooling::newFrontendActionFactory<
        DependencyFrontendAction>(&emitter);

    return Tool.run(factory.get());
}

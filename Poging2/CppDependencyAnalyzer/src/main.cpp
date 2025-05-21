#include "DependencyAnalyzer.h"
#include <clang/Tooling/CommonOptionsParser.h>
#include <clang/Tooling/Tooling.h>
#include <clang/Frontend/FrontendActions.h>
#include <llvm/Support/CommandLine.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/Support/Path.h>
#include <iostream>

using namespace clang;
using namespace clang::tooling;

static llvm::cl::OptionCategory ToolCategory("dependency-analyzer options");
static llvm::cl::opt<std::string> OutputFile("output", llvm::cl::desc("Output DSI file"), llvm::cl::value_desc("filename"), llvm::cl::init("dependencies.dsi"), llvm::cl::cat(ToolCategory));

int main(int argc, const char **argv) {
    auto ExpectedParser = CommonOptionsParser::create(argc, argv, ToolCategory);
    if (!ExpectedParser) {
        llvm::errs() << ExpectedParser.takeError();
        return 1;
    }

    CommonOptionsParser &OptionsParser = ExpectedParser.get();
    ClangTool Tool(OptionsParser.getCompilations(), OptionsParser.getSourcePathList());

    DependencyAnalyzer analyzer(OutputFile);
    std::unique_ptr<FrontendActionFactory> Factory = newFrontendActionFactory<DependencyFrontendAction>(&analyzer);
    return Tool.run(Factory.get());
}
#pragma once
#include <clang/Frontend/FrontendAction.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/ASTMatchers/ASTMatchers.h>
#include <clang/ASTMatchers/ASTMatchFinder.h>
#include <clang/Tooling/Tooling.h>
#include <string>
#include <set>

class DependencyAnalyzer {
public:
    DependencyAnalyzer(const std::string& outputPath);
    void addDependency(const std::string& from, const std::string& to);
    void writeDSI() const;

private:
    std::string outputPath;
    std::set<std::pair<std::string, std::string>> dependencies;
};

class DependencyFrontendAction : public clang::ASTFrontendAction {
public:
    explicit DependencyFrontendAction(DependencyAnalyzer* analyzer);
    std::unique_ptr<clang::ASTConsumer> CreateASTConsumer(clang::CompilerInstance& CI, llvm::StringRef InFile) override;

private:
    DependencyAnalyzer* analyzer;
};
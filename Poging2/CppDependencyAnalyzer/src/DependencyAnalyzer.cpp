#include "DependencyAnalyzer.h"
#include <clang/AST/ASTContext.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Frontend/FrontendPluginRegistry.h>
#include <clang/Tooling/Tooling.h>
#include <llvm/Support/raw_ostream.h>
#include <fstream>
#include <sstream>
#include <filesystem>

using namespace clang;

class AnalyzerVisitor : public RecursiveASTVisitor<AnalyzerVisitor> {
public:
    explicit AnalyzerVisitor(ASTContext* Context, DependencyAnalyzer* analyzer)
        : Context(Context), Analyzer(analyzer) {}

    bool VisitCXXRecordDecl(CXXRecordDecl* Decl) {
        if (Decl->isThisDeclarationADefinition()) {
            std::string typeName = Decl->getQualifiedNameAsString();
            std::string file = Context->getSourceManager().getFilename(Decl->getLocation()).str();
            std::string source = std::filesystem::absolute(file).string() + "." + typeName;

            for (auto method : Decl->methods()) {
                if (method->hasBody()) {
                    for (auto param : method->parameters()) {
                        std::string target = param->getType().getAsString();
                        Analyzer->addDependency(source, target);
                    }
                    std::string ret = method->getReturnType().getAsString();
                    Analyzer->addDependency(source, ret);
                }
            }
        }
        return true;
    }

private:
    ASTContext* Context;
    DependencyAnalyzer* Analyzer;
};

class AnalyzerConsumer : public ASTConsumer {
public:
    explicit AnalyzerConsumer(ASTContext* Context, DependencyAnalyzer* analyzer)
        : Visitor(Context, analyzer) {}

    void HandleTranslationUnit(ASTContext& Context) override {
        Visitor.TraverseDecl(Context.getTranslationUnitDecl());
    }

private:
    AnalyzerVisitor Visitor;
};

DependencyFrontendAction::DependencyFrontendAction(DependencyAnalyzer* analyzer)
    : analyzer(analyzer) {}

std::unique_ptr<ASTConsumer> DependencyFrontendAction::CreateASTConsumer(CompilerInstance& CI, StringRef InFile) {
    return std::make_unique<AnalyzerConsumer>(&CI.getASTContext(), analyzer);
}

DependencyAnalyzer::DependencyAnalyzer(const std::string& outputPath)
    : outputPath(outputPath) {}

void DependencyAnalyzer::addDependency(const std::string& from, const std::string& to) {
    dependencies.emplace(from, to);
}

void DependencyAnalyzer::writeDSI() const {
    std::ofstream out(outputPath);
    out << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<dependencies>\n";
    for (const auto& [from, to] : dependencies) {
        out << "  <dependency>\n";
        out << "    <from>" << from << "</from>\n";
        out << "    <to>" << to << "</to>\n";
        out << "  </dependency>\n";
    }
    out << "</dependencies>\n";
}
#pragma once

#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Frontend/FrontendAction.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Tooling/Tooling.h>
#include "NodeEmitter.h"

class DependencyVisitor : public clang::ASTConsumer,
                           public clang::RecursiveASTVisitor<DependencyVisitor> {
public:
    static void registerEmitter(NodeEmitter* emitter);
    explicit DependencyVisitor(clang::ASTContext* context);

    void HandleTranslationUnit(clang::ASTContext& context) override;
    bool VisitCXXRecordDecl(clang::CXXRecordDecl* Decl);
    bool VisitFunctionDecl(clang::FunctionDecl* Decl);

private:
    clang::ASTContext* context_;
    static inline NodeEmitter* emitter_ = nullptr;
};


// --

#pragma once

#include <clang/AST/RecursiveASTVisitor.h>
#include <memory>
#include "NodeEmitter.h"

class DependencyVisitor : public clang::RecursiveASTVisitor<DependencyVisitor> {
public:
    explicit DependencyVisitor(NodeEmitter& emitter);
    bool VisitCXXRecordDecl(clang::CXXRecordDecl* Decl);
    bool VisitFunctionDecl(clang::FunctionDecl* Decl);
    bool VisitVarDecl(clang::VarDecl* Decl);
    bool VisitEnumDecl(clang::EnumDecl* Decl);

private:
    NodeEmitter& emitter_;
};



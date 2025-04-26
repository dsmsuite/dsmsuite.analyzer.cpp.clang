#pragma once

#include <clang/AST/DeclCXX.h>
#include <clang/AST/Decl.h>
#include <memory>
#include "IGraphRepository.h"

class NodeEmitter {
public:
    explicit NodeEmitter(std::shared_ptr<IGraphRepository> repo);

    void emitClass(const clang::CXXRecordDecl* Decl);
    void emitFunction(const clang::FunctionDecl* Decl);
void emitStruct(const clang::RecordDecl* Decl);
void emitEnum(const clang::EnumDecl* Decl);
void emitVariable(const clang::VarDecl* Decl);
void emitMethod(const clang::CXXMethodDecl* Decl);
void emitInclude(const std::string& includingFile, const std::string& includedFile);
void emitTemplateSpecialization(const clang::ClassTemplateSpecializationDecl* Decl);
private:
    std::shared_ptr<IGraphRepository> repo_;

    void emitBaseClasses(const clang::CXXRecordDecl* Decl, int classId);
    int nextNodeId_ = 1;
    int nextEdgeId_ = 1;

    int emitNode(const std::string& name, const std::string& type, int parentId = -1);
    void emitEdge(int srcId, int tgtId, const std::string& type);
};

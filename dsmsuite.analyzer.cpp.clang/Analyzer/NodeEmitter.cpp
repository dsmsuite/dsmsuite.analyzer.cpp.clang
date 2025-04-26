#include "NodeEmitter.h"
#include "GraphNode.h"
#include "GraphEdge.h"

NodeEmitter::NodeEmitter(std::shared_ptr<IGraphRepository> repo)
    : repo_(std::move(repo)) {}

void NodeEmitter::emitClass(const clang::CXXRecordDecl* Decl) {
    if (!Decl->getIdentifier()) return;
    std::string className = Decl->getQualifiedNameAsString();
    int classId = emitNode(className, "Class");

    emitBaseClasses(Decl, classId);
}

void NodeEmitter::emitBaseClasses(const clang::CXXRecordDecl* Decl, int classId) {
    for (const auto& base : Decl->bases()) {
        const auto* baseType = base.getType()->getAsCXXRecordDecl();
        if (baseType && baseType->getIdentifier()) {
            int baseId = emitNode(baseType->getQualifiedNameAsString(), "Class");
            emitEdge(classId, baseId, "Inheritance");
        }
    }
}

void NodeEmitter::emitFunction(const clang::FunctionDecl* Decl) {
    if (!Decl->getIdentifier()) return;
    std::string name = Decl->getQualifiedNameAsString();
    int funcId = emitNode(name, Decl->isCXXClassMember() ? "Method" : "Function");

    // Return type edge
    if (Decl->getReturnType().getTypePtr()) {
        std::string retType = Decl->getReturnType().getAsString();
        int typeId = emitNode(retType, "Type");
        emitEdge(funcId, typeId, "Return");
    }

    // Parameter edges
    for (const auto* param : Decl->parameters()) {
        std::string paramType = param->getType().getAsString();
        int paramId = emitNode(paramType, "Type");
        emitEdge(funcId, paramId, "Parameter");
    }
}

void NodeEmitter::emitStruct(const RecordDecl* Decl) {
    if (!Decl->getIdentifier()) return;
    if (!Decl->isStruct()) return;

    std::string name = Decl->getQualifiedNameAsString();
    emitNode(name, "Struct");
}

void NodeEmitter::emitEnum(const EnumDecl* Decl) {
    if (!Decl->getIdentifier()) return;

    std::string name = Decl->getQualifiedNameAsString();
    emitNode(name, "Enum");
}

// adds override edge
void NodeEmitter::emitMethod(const CXXMethodDecl* Decl) {
    if (!Decl->getIdentifier()) return;
    std::string name = Decl->getQualifiedNameAsString();
    int methodId = emitNode(name, "Method");

    if (Decl->size_overridden_methods() > 0) {
        for (const auto* overridden : Decl->overridden_methods()) {
            std::string baseName = overridden->getQualifiedNameAsString();
            int baseId = emitNode(baseName, "Method");
            emitEdge(methodId, baseId, "Override");
        }
    }
}

void NodeEmitter::emitVariable(const VarDecl* Decl) {
    if (!Decl->getIdentifier()) return;
    std::string name = Decl->getQualifiedNameAsString();
    emitNode(name, "Variable");
}

void NodeEmitter::emitInclude(const std::string& includingFile, const std::string& includedFile) {
    int srcId = emitNode(includingFile, "File");
    int tgtId = emitNode(includedFile, "File");
    emitEdge(srcId, tgtId, "Include");
}

void NodeEmitter::emitTemplateSpecialization(const ClassTemplateSpecializationDecl* Decl) {
    if (!Decl->getIdentifier()) return;

    std::string name = Decl->getQualifiedNameAsString();
    int tmplInstanceId = emitNode(name, "Class");

    const TemplateArgumentList& args = Decl->getTemplateArgs();
    for (unsigned i = 0; i < args.size(); ++i) {
        const TemplateArgument& arg = args[i];
        if (arg.getKind() == TemplateArgument::Type) {
            QualType qt = arg.getAsType();
            std::string argTypeName = qt.getAsString();
            int argTypeId = emitNode(argTypeName, "Type");

            emitEdge(tmplInstanceId, argTypeId, "TemplateArgument");
        }
    }
}

void NodeEmitter::emitBaseClasses(const CXXRecordDecl* Decl, int classId) {
    for (const auto& base : Decl->bases()) {
        const auto* baseDecl = base.getType()->getAsCXXRecordDecl();
        if (baseDecl && baseDecl->getIdentifier()) {
            std::string baseName = baseDecl->getQualifiedNameAsString();
            int baseId = emitNode(baseName, "Class");

            if (baseDecl->isAbstract()) {
                emitEdge(classId, baseId, "Realizes");
            } else {
                emitEdge(classId, baseId, "Inheritance");
            }
        }
    }
}

// If this method overrides a pure virtual method, it implements it.
//
// ??
//
//for (const auto* overridden : Decl->overridden_methods()) {
//    std::string baseName = overridden->getQualifiedNameAsString();
//    int baseId = emitNode(baseName, "Method");
//
//    emitEdge(methodId, baseId,
//        overridden->isPure() ? "Implements" : "Override");
//}




int NodeEmitter::emitNode(const std::string& name, const std::string& type, int parentId) {
    int id = nextNodeId_++;
    auto node = std::make_shared<GraphNode>(id, name, parentId);
    repo_->saveNode(*node);
    return id;
}

void NodeEmitter::emitEdge(int srcId, int tgtId, const std::string& type) {
    static const std::map<std::string, int> edgeTypeIds = {
        {"Inheritance", 2}, {"Return", 9}, {"Parameter", 8}
    };

    int id = nextEdgeId_++;
    int typeId = edgeTypeIds.at(type);
    auto edge = std::make_shared<GraphEdge>(srcId, tgtId, typeId);
    repo_->saveEdge(*edge);
}

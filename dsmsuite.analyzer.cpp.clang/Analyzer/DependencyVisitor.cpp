#include "DependencyVisitor.h"

using namespace clang;

DependencyVisitor::DependencyVisitor(ASTContext* context) : context_(context) {}

void DependencyVisitor::registerEmitter(NodeEmitter* emitter) {
    emitter_ = emitter;
}

void DependencyVisitor::HandleTranslationUnit(ASTContext& context) {
    TraverseDecl(context.getTranslationUnitDecl());
}

bool DependencyVisitor::VisitCXXRecordDecl(CXXRecordDecl* Decl) {
    if (Decl->isThisDeclarationADefinition()) {
        emitter_->emitClass(Decl);
    }
    return true;
}

bool DependencyVisitor::VisitFunctionDecl(FunctionDecl* Decl) {
    if (Decl->isThisDeclarationADefinition()) {
        emitter_->emitFunction(Decl);
    }
    return true;
}

/// ----------------
 
#include "DependencyVisitor.h"

DependencyVisitor::DependencyVisitor(NodeEmitter& emitter)
    : emitter_(emitter) {}

bool DependencyVisitor::VisitCXXRecordDecl(CXXRecordDecl* Decl) {
    if (Decl->isClass()) emitter_.emitClass(Decl);
    else if (Decl->isStruct()) emitter_.emitStruct(Decl);

    if (auto* spec = llvm::dyn_cast<ClassTemplateSpecializationDecl>(Decl)) {
        emitter_.emitTemplateSpecialization(spec);
    }

    return true;
}

bool DependencyVisitor::VisitFunctionDecl(FunctionDecl* Decl) {
    if (Decl->isCXXClassMember())
        emitter_.emitMethod(llvm::dyn_cast<CXXMethodDecl>(Decl));
    else
        emitter_.emitFunction(Decl);

    return true;
}

bool DependencyVisitor::VisitVarDecl(VarDecl* Decl) {
    emitter_.emitVariable(Decl);
    return true;
}

bool DependencyVisitor::VisitEnumDecl(EnumDecl* Decl) {
    emitter_.emitEnum(Decl);
    return true;
}


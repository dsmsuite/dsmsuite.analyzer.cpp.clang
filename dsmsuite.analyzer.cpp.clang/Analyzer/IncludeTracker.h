#pragma once
#include <clang/Lex/PPCallbacks.h>
#include <clang/Basic/SourceManager.h>
#include "NodeEmitter.h"

class IncludeTracker : public clang::PPCallbacks {
public:
    IncludeTracker(NodeEmitter& emitter, const clang::SourceManager& sm)
        : emitter_(emitter), sm_(sm) {}

    void InclusionDirective(clang::SourceLocation hashLoc,
                            const clang::Token& includeToken,
                            llvm::StringRef fileName,
                            bool isAngled,
                            clang::CharSourceRange filenameRange,
                            const clang::FileEntry* file,
                            llvm::StringRef searchPath,
                            llvm::StringRef relativePath,
                            const clang::Module* imported) override {
        auto srcFile = sm_.getFilename(hashLoc).str();
        auto tgtFile = fileName.str();
        emitter_.emitInclude(srcFile, tgtFile);
    }

private:
    NodeEmitter& emitter_;
    const clang::SourceManager& sm_;
};

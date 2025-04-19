#include "llvm/IR/PassManager.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Support/raw_ostream.h"

#include  <iostream>

#define TEST_TARGET_FUNCTION_NAME "test_main"



using namespace llvm;


namespace {

struct FunctionNamePass : public PassInfoMixin<FunctionNamePass> {

    PreservedAnalyses run(Function &F, FunctionAnalysisManager &FAM) {

        /* 
         * We are not going to apply this to any other functions right now.
         * 
         * Make sure that any test you run has "test_main" with as little
         * content as necessary to apply the transformation. The viz script
         * also exclusively shows the CFG for test_main only.
         * 
         * See ./tests/test.c for a reference.
         */
        if (F.getName().str() != TEST_TARGET_FUNCTION_NAME)
            return PreservedAnalyses::all();
        
        std::cout << "Found function with matching name: " << F.getName().str() << "\n";

        return PreservedAnalyses::all();
    }
};



}

extern "C" ::llvm::PassPluginLibraryInfo LLVM_ATTRIBUTE_WEAK llvmGetPassPluginInfo() {
    return {
        LLVM_PLUGIN_API_VERSION, "FunctionNamePass", "v0.1", [](PassBuilder &PB) {
            PB.registerPipelineParsingCallback([](StringRef Name, FunctionPassManager &FPM, ArrayRef<PassBuilder::PipelineElement>) {
                if(Name == "loop-inverter-improved"){
                    FPM.addPass(FunctionNamePass());
                    return true;
                }
                return false;
            });
        }
    };
}
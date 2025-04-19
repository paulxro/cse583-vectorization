#include "llvm/IR/PassManager.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Support/raw_ostream.h"

#include  <iostream>
#include <vector>

#define TEST_TARGET_FUNCTION_NAME "test_main"


/* I have no idea how to do this on the command line with clang LOL */
#define DEBUG

using namespace llvm;




#ifdef DEBUG
void _print_first_instr_in_loop(Loop *loop) {
    if (!loop)
        return;
    
    for (BasicBlock *bb : loop->getBlocks()) {
        for (Instruction &instr : *bb) {
            instr.print(errs());
            errs() << "\n";
            break;
        }
        break;
    }
}
#else
void _print_first_instr_in_loop(Loop *loop) {}
#endif


namespace {

struct LoopInversionPass : public PassInfoMixin<LoopInversionPass> {
    /*
     * Returns a vector of Loop* vectors.
     *
     * Each element in the top level vector is a vector of Loop*
     * where the inner-vector denotes the loops involved in a nest.
     * 
     * Note that this only works for double-nested loops, since
     * LI can only see top-level loops, and we only look one
     * level deep. This should be enough for our purposes.
     * 
     * For the tests we have discussed so far:
     *      - Outer vector size is expected (1): one nested loop
     *      - Inner vector size is expected (2): two loops in nest
     */
    std::vector<std::vector<Loop *>> collect_loops(LoopInfo &LI) {
        std::vector<std::vector<Loop *>> nested_loops;

        for (Loop *loop : LI.getTopLevelLoops()) {
            std::vector<Loop *> nested_loop = {loop};

            for (Loop *sub_loop : loop->getSubLoops()) {
                nested_loop.push_back(sub_loop);
            }

            nested_loops.push_back(nested_loop);
        }

        return nested_loops;
    }



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

        llvm::LoopAnalysis::Result &li = FAM.getResult<LoopAnalysis>(F);
        
        auto nested_loops = collect_loops(li);

        if (!nested_loops.size() || nested_loops.at(0).size() < 2)
            return PreservedAnalyses::all();
        
        Loop *outer_loop = nested_loops.at(0).at(0);
        Loop *inner_loop = nested_loops.at(0).at(1);

        _print_first_instr_in_loop(outer_loop);
        _print_first_instr_in_loop(inner_loop);

        return PreservedAnalyses::all();
    }
};



}

extern "C" ::llvm::PassPluginLibraryInfo LLVM_ATTRIBUTE_WEAK llvmGetPassPluginInfo() {
    return {
        LLVM_PLUGIN_API_VERSION, "LoopInversionPass", "v0.1", [](PassBuilder &PB) {
            PB.registerPipelineParsingCallback([](StringRef Name, FunctionPassManager &FPM, ArrayRef<PassBuilder::PipelineElement>) {
                if(Name == "loop-inverter-improved"){
                    FPM.addPass(LoopInversionPass());
                    return true;
                }
                return false;
            });
        }
    };
}
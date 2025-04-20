#include "llvm/IR/PassManager.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Transforms/Utils/Cloning.h"

#include  <iostream>
#include <vector>

#define TEST_TARGET_FUNCTION_NAME "test_main"

/*
 * Turns out we need to build OPT in DEBUG mode
 * instead of RELEASE mode to use LLVM_DEBUG.
 * Rather just use this macro, make sure to unset.
*/
#define DEBUG

using namespace llvm;

void _print_first_instr_in_loop(Loop *loop) {
    #ifdef DEBUG

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

    #endif
}



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

    /*
     * Duplicates all BasicBlocks in blocks according to VMap, into F.
     *
     * Turns out that LLVM gets really upset if you just try to duplicate
     * instructions directly. Instead, it wants a VMap, which maintains
     * some notion of cross-instruction references internally.
     * 
     * When the BasicBlock is cloned (using CloneBasicBlock) it knows
     * what v-regs were referenced in the original code, and makes it so that we
     * are referring to the new ones in the duplicated instructions. E.g.
     * 
     * ORIGINAL                  DUPLICATED
     * 
     * %1 = [something]      |  %3 = [something]
     * %2 = %1 + [something] |  %4 = %3 + [something] <-- Note that %4 uses %3, not %1
     * 
     * Because our limited examples use arrays passed as parameters, LLVM
     * gets upset about duplicated instructions not knowning what
     * they are referring to in a void (e.g. it doesn't know how 
     * to reference "a"). So we have to necessarily tie the duplicated blocks
     * to the function.
     * 
     * @TODO: I HAVE NO IDEA WHERE THESE ARE ACTUALLY DUPLICATED IN THE FUNCTION.
     *      DRAWING THE CFG DOESN'T SHOW THESE CHANGES, AND READING THE .LL FILE 
     *      HURTS MY BRAIN.
     */
    std::vector<BasicBlock *> duplicate_bbs(std::vector<BasicBlock *> blocks, ValueToValueMapTy &VMap, Function *F) {
        std::vector<BasicBlock *> duplicated_blocks;

        for (BasicBlock *bb : blocks) {
            BasicBlock *clone = CloneBasicBlock(bb, VMap, ".clone", F);
            VMap[bb] = clone;
            duplicated_blocks.push_back(clone);
        }

        return duplicated_blocks;
    }

    bool loop_contains_bb(Loop *loop, BasicBlock *bb) {
        for (BasicBlock *loop_block : loop->getBlocks())
            if (bb == loop_block)
                return true;
        return false;
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

        std::vector<BasicBlock*> bbs_to_duplicate;
        ValueToValueMapTy VMap;

        for (BasicBlock *bb : outer_loop->getBlocks())
            if (!loop_contains_bb(inner_loop, bb))
                bbs_to_duplicate.push_back(bb);

        std::vector<BasicBlock *> cloned_bbs = duplicate_bbs(bbs_to_duplicate, VMap, &F);
        
        for (BasicBlock &BB : F) {
            BB.print(errs());
        }


        return PreservedAnalyses::none();
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
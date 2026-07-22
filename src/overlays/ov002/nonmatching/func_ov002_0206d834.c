/* NOT MATCHING -- one instruction of register allocation, everything else exact.
 *
 * Size 56/56, identical instruction stream, identical relocs. The single residue
 * is at offset 2: the ROM opens with `adds r2, r0, #0`, moving the flag out of
 * r0 so r0 can be the scratch for both literal-pool loads. mwcc keeps the flag
 * in r0 and uses r2 as the scratch instead, so every instruction between there
 * and the first branch carries the mirrored register pair.
 *
 * Ruled out on the SOURCE axis (six forms, all failing identically at 0x2):
 *   1. base pointer in a local declared before the test (the form kept here);
 *   2. base expression inlined into the else arm only;
 *   3. the flag copied into its own local first;
 *   4. the reason halfword read into a local before the branch;
 *   5. the arms swapped (`if (plain == 0)` first);
 *   6. if/else instead of early return; and a trailing unused third parameter.
 *
 * Ruled out on the SIGNATURE axis, which is the lever that broke the two ov010
 * parks: making the function return int and both arms `return OS_SPrintf(...)`.
 * A non-void return reserves r0 and is exactly the kind of thing that would
 * force the flag out of it -- it does not here.
 *
 * Ruled out on the BUILD axis: `tools/build_sweep.py` -- all 26 usable builds
 * (1.2 sp*, 2.0 sp*, 3.0_136_patched, 3.0_patch4, dsi 1.1..1.6sp2) are
 * identically 26 bytes off; 3.0_136 fails to compile. No build is closer, so
 * this is not a compiler-version question.
 *
 * NOT ruled out: OS_SPrintf's real prototype. It is declared K&R-variadic here
 * because the ROM calls it with two arguments in one arm and three in the other,
 * and the 2-argument call will not compile against a fixed 3-parameter
 * declaration. If the NitroSDK header's exact spelling turns out to change the
 * argument setup, that is the axis left untried.
 *
 * The semantics below are correct and worth keeping: root + 0x8ba8 is the same
 * Ov002ResultContext base func_ov002_02068fc4 reaches through
 * NNSi_FndGetCurrentRootHeap, which is what establishes that
 * data_ov002_0207fa00 holds the root heap block.
 */
/* Format the result line into the caller's buffer: the plain form when the flag
 * is set, otherwise the form that takes the result screen's SIGNED reason code.
 *
 * The reason lives at root + 0x8ba8 + 2 -- the same Ov002ResultContext base
 * func_ov002_02068fc4 reaches through NNSi_FndGetCurrentRootHeap, which is what
 * establishes that data_ov002_0207fa00 holds the root heap block. */
typedef struct {
    short nUnk00;           /* +0x00 */
    short nReason;          /* +0x02 signed */
} Ov002ResultContext;

extern void OS_SPrintf();

extern int data_ov002_0207fa00;
extern char data_ov002_0207efe0[];
extern char data_ov002_0207efe4[];

void func_ov002_0206d834(int plain, char *buf) {
    Ov002ResultContext *result = (Ov002ResultContext *)(data_ov002_0207fa00 + 0x8ba8);

    if (plain != 0) {
        OS_SPrintf(buf, data_ov002_0207efe0);
        return;
    }
    OS_SPrintf(buf, data_ov002_0207efe4, result->nReason);
}

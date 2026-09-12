/*
 * Reload guard around an object's section-relocation dispatch: save the global
 * reentrancy flag data_020427f0, set it, relocate/dispatch pFile (the 'KAPH'
 * relocation path when tagged, or the plain post-load hook otherwise), restore
 * the flag, run the real load-finish handler func_0202a208, then clear the
 * handle at pSlot[3] and hand back the handler's result.
 *
 * Returning func_0202a208's result is what keeps r0 live to the epilogue, so
 * the trailing `pSlot[3] = 0` materialises its zero in r1; declared `void`,
 * mwcc puts that zero in r0. The sibling func_0202a388 (the other caller of
 * func_0202a208, already matched) likewise returns int.
 */

extern void func_02025464(unsigned int *param_1, int param_2);
extern void func_02025138(unsigned int *pRes);
extern int func_0202a208(int a, int b, int c, int d);
extern int data_020427f0;

int func_0202a3cc(unsigned int *pSlot, int nNode, unsigned int *pFile, int nHeap)
{
    int save = data_020427f0;
    int result;
    data_020427f0 = 1;
    if (*pFile == 0x4850414b) {
        func_02025464(pFile, 1);
    } else {
        func_02025138(pFile);
    }
    data_020427f0 = save;
    result = func_0202a208((int)pSlot, nNode, (int)pFile, nHeap);
    pSlot[3] = 0;
    return result;
}

/* func_ov002_020739ec -- (re)create slot `i` of the ov002 scene's object table (+0x1c of the root
 * context) and hand the new object to the shared registrar.
 *
 * The slot is stored and then RE-READ, and the re-read has to happen before the registrar's first
 * argument is computed -- that is the ROM's `str r0,[r5,r4] ; ldr r4,[r5,r4] ; bl`. Writing the
 * call as `f(*g(), slots[i])` lets mwcc sink the load past the `bl`; binding the FIRST argument to
 * its own local first pins the order. (This is the function state.md listed as "mwcc
 * rematerialises slots[idx] after the call where the ROM loads it before" -- it was an
 * evaluation-order problem, not a rematerialisation one.) */
extern int func_ov107_020c1f28(int i);
extern int *OS_IsThreadAvailable_0x020c9848(void);
extern void func_ov107_020c2b20(int a, int b);
extern int data_ov002_0207fa14;

void func_ov002_020739ec(int i) {
    int *slots = (int *)(*(int *)&data_ov002_0207fa14 + 0x1c);
    int v;
    slots[i] = func_ov107_020c1f28(i);
    v = slots[i];
    {
        int h = *OS_IsThreadAvailable_0x020c9848();
        func_ov107_020c2b20(h, v);
    }
}

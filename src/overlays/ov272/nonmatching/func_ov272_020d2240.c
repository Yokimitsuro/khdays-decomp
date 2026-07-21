/* AI wait-tick: accumulate the timer (node+0x50 += owner delta); once past 0x1000, reset it,
 * stamp a fixed marker (0xffff6216) at node+0x64, seed a random value (0x2000 + d0x1001) at
 * node+0x68, and hand off to the next state. Representative of a 3-overlay byte-identical group
 * (ov119/ov272/ov279).
 *
 * NON-MATCHING (scheduling tie). Semantics, registers and constants are all exact; the only
 * residue is one instruction slot: mwcc 139 -O4,p hoists the pooled `ldr r1,=0xffff6216` load into
 * the slot right after `mov r0,#0`, i.e. above the `str r0,[node+0x50]` (state[0x14]=0) store,
 * whereas the ROM emits the store first and loads the constant afterwards. Reordering the two
 * stores only swaps which store leads; a variable for the RNG range does not move it (confirmed by
 * the earlier analysis in the Ghidra plate comment). A load-scheduling heuristic difference. */
extern int func_02023eb4();
extern void func_0203c634(int self, int idx, void *cb);
extern void func_ov272_020d22a4(void);

void func_ov272_020d2240(int *param_1) {
    int node = param_1[1];
    int sum;
    sum = *(int *)(node + 0x50) + *(int *)(*param_1 + 0x2c);
    *(int *)(node + 0x50) = sum;
    if (sum < 0x1000) {
        return;
    }
    *(int *)(node + 0x50) = 0;
    *(int *)(node + 0x64) = 0xffff6216;
    *(int *)(node + 0x68) = func_02023eb4(0x1001) + 0x2000;
    func_0203c634((int)param_1, *(signed char *)((char *)param_1 + 0x20), &func_ov272_020d22a4);
}

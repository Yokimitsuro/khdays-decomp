/* Play the "surprised" cue: copy the two-halfword cue params from the shared table (data_020d63c0
 * +8) and, if the object's cue vtable slot (*node+0x24) is set, invoke it; then cancel the current
 * action (mode 0xd) and register the recover callback.
 *
 * NON-MATCHING (scheduling tie, singleton). Semantics/registers/constants exact; the only residue
 * is where the `ldr node,[self+4]` and the `add r1,sp` (&cue) land: the ROM interleaves the node
 * load between the two `ldrh` cue reads and the two `strh` stores and materialises &cue early,
 * whereas mwcc 139 does both stores first then loads node (node-before-copy schedules it one slot
 * too early instead). A load-scheduling heuristic difference. */
extern void func_ov107_020c9264(int owner, int mode, int b);
extern void func_0203c634(int self, int idx, void *cb);
extern unsigned short data_ov236_020d63c0[];
extern void func_ov236_020d0b88(void);

void func_ov236_020d0b20(int param_1) {
    unsigned short cue[2];
    int *node;
    void (*fn)(int obj, void *arg, int n);
    cue[0] = data_ov236_020d63c0[4];
    cue[1] = data_ov236_020d63c0[5];
    node = *(int **)(param_1 + 4);
    fn = *(void (**)(int, void *, int))(*node + 0x24);
    if (fn != 0) {
        fn(*node, cue, 4);
    }
    func_ov107_020c9264(*node, 0xd, 0);
    func_0203c634(param_1, *(signed char *)((char *)param_1 + 0x20), &func_ov236_020d0b88);
}

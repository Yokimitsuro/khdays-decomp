/*
 * [nonmatching: &&-chain 1-register coloring: the original loads the *(arg0+0x4ec) pointer into r1 (kept for the +4 deref); mwcc uses r0. Identical instructions, one register differs]
 *
 * Structurally equivalent; mwcc 3.0/139 diverges only in the noted register
 * allocation. Left uncarved (byte-exact in the blob).
 */
extern int func_ov022_020882bc(unsigned int arg0);
extern int func_01fffe14(void);
extern void func_ov107_020c1fb4(void);

void func_ov022_020a0f60(int arg0) {
    unsigned int s = func_ov022_020882bc(*(unsigned char *)(arg0 + 9));
    int a = func_01fffe14();
    int off;
    if (s == a && *(int *)(arg0 + 0x4ec) != 0 &&
        *(int *)(*(int *)(arg0 + 0x4ec) + 4) != 0) {
        func_ov107_020c1fb4();
    }
    off = 0x4b4;
    *(int *)(arg0 + off) = 0xf000;
    *(int *)(arg0 + off - 0x30) = 0;
    *(int *)(arg0 + off - 0x34) = *(int *)(arg0 + off - 0x30);
    *(int *)(arg0 + off - 0x38) = *(int *)(arg0 + off - 0x34);
}

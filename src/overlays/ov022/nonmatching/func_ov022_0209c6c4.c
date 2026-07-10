/*
 * [nonmatching: the original spills param_1 to the pushed-r3 scratch slot and reloads it for the final call; mwcc holds it in a callee-saved reg, flipping the a/b/i coloring]
 *
 * Structurally equivalent; mwcc 3.0/139 diverges only in the noted register
 * allocation / scheduling. Left uncarved (byte-exact in the blob).
 */
extern void func_ov002_02051c88(int arg0);
extern void func_ov022_020b07f0(unsigned int *arg0, int arg1);

void func_ov022_0209c6c4(int arg0, int arg1, int arg2, int arg3) {
    int a = arg0;
    int b = arg0 + 0xda8;
    int i = 0;
    do {
        if (*(char *)(a + 0xda9) != 0) func_ov002_02051c88(b);
        i = i + 1;
        a = a + 0x164;
        b = b + 0x164;
    } while (i < 2);
    func_ov022_020b07f0((unsigned int *)(arg0 + 0x910), 0x910);
}

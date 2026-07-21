/* Begin the recoil slide: flag the owner charging bit (*node+0x390), clear the hw60 high-byte
 * "grounded" bit 0x80, roll a random slide duration into node[2], and register the think callback. */
extern int func_02023eb4();
extern void func_0203c634(int self, int idx, void *cb);
extern void func_ov273_020d65fc(void);

void func_ov273_020d6590(int param_1) {
    int *node = *(int **)(param_1 + 4);
    int v;
    unsigned short hw60;
    *(int *)(*node + 0x390) = 1;
    hw60 = *(unsigned short *)(*node + 0x60);
    *(unsigned short *)(*node + 0x60) =
        (hw60 & ~0xff00) | ((unsigned int)(unsigned short)(((unsigned int)hw60 << 0x10) >> 0x18 & 0xffffff7f) << 0x18 >> 0x10);
    node[2] = func_02023eb4(0x801) + (v - v);
    func_0203c634(param_1, *(signed char *)((char *)param_1 + 0x20), &func_ov273_020d65fc);
}

/* Release entry: clears bit 1 of the +4 child's +0x5c, installs the 020ced6c handler at its
 * +0x6c and back-links the state at its +0x84, binds its channels 0 / 4 / 1 / 2 with (0, 0),
 * re-inits it, clears the +8 word, installs 020ceee4 on slot 2 and moves the node to 020ceee8. */
extern void func_0203b9fc(int obj, int slot, int a, int b);
extern void func_0203c7ac(int obj, int a);
extern void func_0203c634(int self, int idx, void *cb);
extern void func_ov244_020ced6c(void);
extern void func_ov244_020ceee4(void);
extern void func_ov244_020ceee8(void);

void func_ov244_020cee08(int param_1) {
    int *node = *(int **)(param_1 + 4);
    *(int *)(node[1] + 0x5c) &= ~2;
    *(void **)(node[1] + 0x6c) = (void *)&func_ov244_020ced6c;
    *(int **)(node[1] + 0x84) = node;
    func_0203b9fc(node[1], 0, 0, 0);
    func_0203b9fc(node[1], 4, 0, 0);
    func_0203b9fc(node[1], 1, 0, 0);
    func_0203b9fc(node[1], 2, 0, 0);
    func_0203c7ac(node[1], 0);
    node[2] = 0;
    func_0203c634(param_1, 2, &func_ov244_020ceee4);
    func_0203c634(param_1, *(signed char *)((char *)param_1 + 0x20), &func_ov244_020ceee8);
}

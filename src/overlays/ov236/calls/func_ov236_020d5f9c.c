/* Release entry: for each of the two children (+4 / +8) clear bit 1 of +0x5c, bind channel 0
 * with (0, 0), 1 with (0, 0), 2 with (0, 0) and 4 with (0, 0), then re-init it; the node moves to
 * 020d6094. */
extern void func_0203b9fc(void *child, int cmd, int arg, int flag);
extern void func_0203c7ac(void *child, int a);
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov236_020d6094(void);

void func_ov236_020d5f9c(int *node) {
    int *state = (int *)node[1];
    int i;
    for (i = 0; i < 2; i++) {
        *(int *)(state[i + 1] + 0x5c) &= ~2;
        func_0203b9fc((void *)state[i + 1], 0, 0, 0);
        func_0203b9fc((void *)state[i + 1], 1, 0, 0);
        func_0203b9fc((void *)state[i + 1], 2, 0, 0);
        func_0203b9fc((void *)state[i + 1], 4, 0, 0);
        func_0203c7ac((void *)state[i + 1], 0);
    }
    func_0203c634(node, *(signed char *)(node + 8), func_ov236_020d6094);
}

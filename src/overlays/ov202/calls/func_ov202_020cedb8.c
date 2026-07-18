extern void func_0203b9fc(void *p, int a, int b, int c);
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov202_020ced70(void);
extern void func_ov202_020cee60(void);

void func_ov202_020cedb8(char *obj) {
    int *state = *(int **)(obj + 4);
    int *sub = *(int **)(*(int *)(*state + 0x3dc));
    state[1] = (int)sub;
    *(void **)((char *)sub + 0x6c) = func_ov202_020ced70;
    *(int **)(state[1] + 0x84) = state;
    *(int *)(state[1] + 0x5c) &= ~2;
    func_0203b9fc((void *)state[1], 2, 0, 0);
    func_0203b9fc((void *)state[1], 0, 0, 0);
    func_0203c634(obj, *(signed char *)(obj + 0x20), func_ov202_020cee60);
}

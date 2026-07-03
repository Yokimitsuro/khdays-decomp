struct hw { unsigned short lo:8, hi:8; };

extern int func_ov107_020cab14(int a, int b);
extern void VEC_Subtract(void *a, void *b, void *out);
extern int func_020050b4(int a, int b);
extern void func_ov107_020c9264(int a, int b, int c);
extern void func_0203c634(int node, int slot, void *cb);
extern void func_ov131_020cd160(void);

void func_ov131_020cd098(int *param_1) {
    int *state = (int *)param_1[1];
    int sp[3];
    int acc = state[0xc] + *(int *)(*param_1 + 0x2c);
    state[0xc] = acc;
    if (acc < 0x6ee) return;
    {
        int target = func_ov107_020cab14(*state, 0);
        state[2] = target;
        if (target != 0) {
            int angle;
            VEC_Subtract((void *)(target + 0x74), (void *)state[0x11], sp);
            angle = func_020050b4(sp[0], sp[2]);
            state[4] = angle;
            state[3] = angle;
        }
    }
    ((struct hw *)(*state + 0x60))->hi &= ~0x82;
    func_ov107_020c9264(*state, 0, 0);
    func_0203c634((int)param_1, *(signed char *)((int)param_1 + 0x20), &func_ov131_020cd160);
}

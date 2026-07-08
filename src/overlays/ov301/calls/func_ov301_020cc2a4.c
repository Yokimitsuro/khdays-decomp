struct flag8 {
    unsigned value : 8;
};

extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov301_020cc63c(void);
extern void func_ov301_020cc338(void);
extern void func_ov301_020cc458(void);

void func_ov301_020cc2a4(int *node)
{
    int *state = (int *)node[1];

    *(signed char *)(*state + 0x1c6) = 0;
    *(signed char *)(*state + 0x1c7) = -1;
    ((struct flag8 *)(*(int *)(*state + 0x388) + 8))->value &= ~1;
    state[1] = *state + 0xb0;
    func_0203c634(node, 1, func_ov301_020cc63c);
    func_0203c634(node, 0, func_ov301_020cc338);
    func_0203c634(node, 2, func_ov301_020cc458);
}

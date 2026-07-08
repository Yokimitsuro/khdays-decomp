extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov299_020d3a9c(void);
extern void func_ov299_020d3b14(void);
extern void func_ov299_020d3b18(void);

void func_ov299_020d3a30(int *node)
{
    int *state = (int *)node[1];

    *(signed char *)(*state + 0x1c6) = 0;
    *(signed char *)(*state + 0x1c7) = -1;
    state[1] = *state + 0xb0;
    func_0203c634(node, 1, func_ov299_020d3b18);
    func_0203c634(node, 0, func_ov299_020d3a9c);
    func_0203c634(node, 2, func_ov299_020d3b14);
}

extern void func_ov107_020c9264();
extern void func_0203c634();
extern void func_ov135_020d1a84();
void func_ov135_020d1a38(int param_1)
{
    int *state = *(int **)(param_1 + 4);
    if (*(unsigned char *)(state[1] + 0xad) != 0)
        return;
    func_ov107_020c9264(state[0], 7, 1);
    state[0xc] = 0;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), func_ov135_020d1a84);
}

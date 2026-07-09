extern void func_ov107_020c9264();
extern void func_0203c634();
extern void func_ov121_020cfb54();
void func_ov121_020cfb10(int param_1)
{
    int state = *(int *)(param_1 + 4);
    if (*(unsigned char *)*(int *)(state + 0x48) != 0)
        return;
    func_ov107_020c9264(*(int *)state, 0xa, 0);
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), func_ov121_020cfb54);
}

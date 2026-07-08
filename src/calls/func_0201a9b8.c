extern int func_02019cb8();
int func_0201a9b8(int param_1, int param_2, int param_3)
{
    unsigned int mask = 0;
    int i = 0;
    if (param_2 > 0) {
        do {
            *(unsigned char *)(param_1 + i + 0x4c) = *(unsigned char *)(param_3 + i);
            mask |= 1 << *(unsigned char *)(param_3 + i);
            i++;
        } while (i < param_2);
    }
    if (func_02019cb8(mask) == 0)
        return 0;
    *(int *)(param_1 + 0x48) = param_2;
    *(unsigned int *)(param_1 + 0x44) = mask;
    return 1;
}

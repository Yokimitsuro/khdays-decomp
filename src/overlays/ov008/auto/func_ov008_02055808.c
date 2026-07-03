int func_ov008_02055808(int param_1, unsigned int param_2)
{
    int i = 0;
    if (0 < *(int *)(param_1 + 0x30)) {
        int entry = *(int *)(param_1 + 0xc);
        int off = 0;
        do {
            if ((*(int *)(entry + 0x14) != 0) &&
                (param_2 == *(unsigned short *)(*(int *)(param_1 + 0xc) + off)))
                break;
            i = i + 1;
            entry = entry + 0x38;
            off = off + 0x38;
        } while (i < *(int *)(param_1 + 0x30));
    }
    return i * 0x38 + *(int *)(param_1 + 0xc);
}

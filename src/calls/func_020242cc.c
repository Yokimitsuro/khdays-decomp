extern unsigned short data_02041dd4[];
int func_020242cc(int param_1) {
    unsigned short h = data_02041dd4[param_1];
    if (h == 0) return param_1;
    if (*(unsigned short *)(h + 0x4000000) & 0x2000) return param_1 + 2;
    return param_1;
}

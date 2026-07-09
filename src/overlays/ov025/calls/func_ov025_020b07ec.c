extern void MI_CpuFill8();

void func_ov025_020b07ec(int *arg0, int *arg1) {
    int v;
    MI_CpuFill8(arg0, 0, 0x14);
    arg0[0] = (int)arg1;
    v = *arg1;
    arg0[1] = (int)arg1 + v;
    arg0[2] = (int)arg1 + v;
    arg0[3] = arg0[1] + *(int *)(arg0[1] + 8);
    arg0[4] = *(unsigned char *)(arg1 + 1);
}

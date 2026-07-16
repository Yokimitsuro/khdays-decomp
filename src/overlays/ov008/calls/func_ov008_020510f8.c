extern void func_02034258();
extern int data_ov008_02090f04;

void func_ov008_020510f8(int arg0) {
    int v = *(int *)(*(int *)((char *)&data_ov008_02090f04 + 4) + arg0 * 4 + 0x96bc);
    if (v < 1) return;
    if (v == 1) func_02034258(arg0);
    {
        int base = *(int *)((char *)&data_ov008_02090f04 + 4) + 0x96bc;
        *(int *)(base + arg0 * 4) = *(int *)(base + arg0 * 4) - 1;
    }
}

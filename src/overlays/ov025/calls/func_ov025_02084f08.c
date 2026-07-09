extern void func_02034258();
extern int data_ov025_020b5744;

void func_ov025_02084f08(int arg0) {
    int v = *(int *)(*(int *)((char *)&data_ov025_020b5744 + 4) + arg0 * 4 + 0x96bc);
    if (v < 1) return;
    if (v == 1) func_02034258(arg0);
    {
        int base = *(int *)((char *)&data_ov025_020b5744 + 4) + 0x96bc;
        *(int *)(base + arg0 * 4) = *(int *)(base + arg0 * 4) - 1;
    }
}

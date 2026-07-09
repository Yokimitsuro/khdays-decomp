extern void MI_CpuCopy8();
extern int data_ov025_020b5754;

int func_ov025_020899dc(int arg0) {
    int g = data_ov025_020b5754;
    if (g == 0) {
        return 0;
    }
    MI_CpuCopy8(g, arg0, 8);
    return arg0;
}

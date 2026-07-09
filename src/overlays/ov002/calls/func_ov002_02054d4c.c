extern void MI_CpuCopy8();
extern int data_ov002_0207f610;

int func_ov002_02054d4c(int arg0) {
    int p = *(int *)&data_ov002_0207f610;
    if (p == 0) {
        return 0;
    }
    MI_CpuCopy8(p, arg0, 8);
    return arg0;
}

extern void MI_CpuCopy8();
extern int data_ov002_0207f62c;

void func_ov002_0206374c(int arg0) {
    int p = *(int *)((char *)&data_ov002_0207f62c + 4);
    MI_CpuCopy8(arg0, p + 0x17c, 0xc);
    *(int *)(p + 0x9c) = 1;
}

extern int func_ov002_0205dae4();
extern int data_ov002_0207f614;

void func_ov002_02056d48(void) {
    int p = *(int *)&data_ov002_0207f614;
    *(short *)(p + 0x1a4) = func_ov002_0205dae4();
    *(char *)(p + 0x1ac) = 4;
    *(int *)(p + 0x1a8) = 0;
}

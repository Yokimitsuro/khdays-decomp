extern int data_ov002_0207f628;

void func_ov002_02061c14(int arg0) {
    int p = *(int *)&data_ov002_0207f628;
    if (p != 0) {
        *(int *)(p + 0x50) = arg0;
    }
}

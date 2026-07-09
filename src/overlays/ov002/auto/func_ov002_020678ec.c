extern int data_ov002_0207f9fc;

void func_ov002_020678ec(int arg0, int arg1) {
    int p = *(int *)&data_ov002_0207f9fc;
    if (p != 0) {
        *(int *)(p + 0x1a8) = arg0;
        *(int *)(p + 0x1ac) = arg1;
    }
}

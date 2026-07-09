extern int data_ov002_0207f99c;

void func_ov002_020662b8(void) {
    int p = *(int *)&data_ov002_0207f99c;
    if (p != 0) {
        *(int *)(p + 0x14) = 0;
    }
}

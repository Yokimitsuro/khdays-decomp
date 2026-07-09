extern int data_ov002_0207f62c;

int func_ov002_02063888(void) {
    int p = *(int *)((char *)&data_ov002_0207f62c + 4);
    if (p == 0) {
        return 0;
    }
    return *(int *)(p + 8) != 0;
}

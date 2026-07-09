extern int data_ov002_0207f628;

int func_ov002_02061c2c(void) {
    int p = *(int *)&data_ov002_0207f628;
    if (p == 0) {
        return 0;
    }
    return *(int *)(p + 0xe4) == 1;
}

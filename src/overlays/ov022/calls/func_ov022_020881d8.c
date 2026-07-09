extern int data_ov022_020b2e78;
unsigned int func_ov022_020881d8(void) {
    unsigned int *p = ((unsigned int **)&data_ov022_020b2e78)[1];
    if (p == 0) return 0;
    return *p & 1;
}

extern int data_ov022_020b2e78;
unsigned char func_ov022_020882f8(void) {
    int p = ((int *)&data_ov022_020b2e78)[1];
    if (p == 0) return 0;
    return *(unsigned char *)(p + 0x34);
}

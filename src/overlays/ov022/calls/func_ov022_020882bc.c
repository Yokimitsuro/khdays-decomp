extern int data_ov022_020b2e78;
unsigned char func_ov022_020882bc(int arg0) {
    int p = ((int *)&data_ov022_020b2e78)[1];
    if (p == 0) return 0;
    return *(unsigned char *)(arg0 * 0xc + p + 0xe);
}

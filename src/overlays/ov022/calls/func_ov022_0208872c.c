extern int data_ov022_020b2e78;
void func_ov022_0208872c(int arg0) {
    int p = ((int *)&data_ov022_020b2e78)[1];
    unsigned char v;
    unsigned char *b;
    if (p == 0) return;
    v = arg0;
    b = (unsigned char *)(p + 0x3c);
    *b = (*b & ~2) | ((unsigned int)(v << 0x1f) >> 0x1e);
}

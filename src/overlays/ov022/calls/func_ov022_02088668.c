extern int data_ov022_020b2e78;
unsigned int func_ov022_02088668(void) {
    int p = ((int *)&data_ov022_020b2e78)[1];
    if (p == 0) return 0;
    return ((unsigned int)*(unsigned char *)(p + 0x3c) << 0x1b) >> 0x1f;
}

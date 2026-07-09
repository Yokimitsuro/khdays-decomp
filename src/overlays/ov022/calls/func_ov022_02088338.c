extern int data_ov022_020b2e78;
extern short func_02030788(void);
unsigned int func_ov022_02088338(void) {
    int p = ((int *)&data_ov022_020b2e78)[1];
    if (p == 0) return 0;
    if (func_02030788() == 0) return 1;
    return ((unsigned int)*(unsigned char *)(p + 0x3c) << 0x1c) >> 0x1f;
}

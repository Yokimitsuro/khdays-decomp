extern int data_ov022_020b2e78;
extern unsigned short func_020362fc(unsigned short *arg0);
unsigned short func_ov022_02088cdc(void) {
    int p = ((int *)&data_ov022_020b2e78)[1];
    if (p != 0) return func_020362fc((unsigned short *)(p + 0x4c));
    return 0;
}

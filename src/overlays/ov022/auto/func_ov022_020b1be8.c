void func_ov022_020b1be8(unsigned char *arg0, unsigned char arg1) {
    *arg0 = 0;
    *(short *)(arg0 + 4) = -1;
    *(short *)(arg0 + 2) = *(short *)(arg0 + 4);
    arg0[6] = arg1;
}

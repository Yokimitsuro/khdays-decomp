extern unsigned short data_02044660;

void func_020030c4(int bit) {
    int mask = ~(1 << bit);
    data_02044660 &= mask;
}

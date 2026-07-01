extern unsigned short data_02044660;

void OSi_ClearAlarmBit(int bit) {
    int mask = ~(1 << bit);
    data_02044660 &= mask;
}

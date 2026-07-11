/* Spin while the masked bits of the halfword at data_02046390+0x3a stay set. */
extern char data_02046390;

void func_0200ca50(unsigned int mask) {
    while (*(volatile unsigned short *)(&data_02046390 + 0x3a) & mask) {
    }
}

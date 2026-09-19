/* Reset the +0x2d34 request pair (byte 0 cleared, bit 1 of byte 1 cleared), then bind the
 * data_ov043_020b5850 script on the +0x2c2c block at a rate of the +9 level plus 7. */
extern void func_0202a634(int a, int b, int c, int d);
extern int data_ov043_020b5850;

void func_ov043_020b37dc(int this_) {
    unsigned char *r = (unsigned char *)(this_ + 0x2c2c);
    r[0x108] = 0;
    r[0x109] &= ~2;
    func_0202a634((int)r, (int)&data_ov043_020b5850, 1, *(unsigned char *)(this_ + 9) + 7);
}

#pragma thumb on
extern void func_0202a7dc(int this_);
extern void func_0202ba18(unsigned char *sub);

void func_ov015_02081978(char *obj) {
    func_0202a7dc((int)(obj + 0x61c));
    func_0202ba18((unsigned char *)(obj + 0x498));
    *(unsigned short *)(obj + 0x12) &= ~4;
}

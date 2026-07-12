/* Run func_ov002_020540f0(param_1); if bit0 of its flag byte (+0x2c) is now set,
 * also run func_ov002_02054290(param_1). A 1-bit bitfield reproduces the ROM's
 * lsl#31;lsrs#31 bit0 extraction (a plain & 1 becomes tst, an int shift becomes asr). */
extern void func_ov002_020540f0(int obj);
extern void func_ov002_02054290(int obj);

struct flag2c { unsigned char active : 1; };

void func_ov002_02054430(int param_1) {
    func_ov002_020540f0(param_1);
    if (((struct flag2c *)(param_1 + 0x2c))->active) {
        func_ov002_02054290(param_1);
    }
}

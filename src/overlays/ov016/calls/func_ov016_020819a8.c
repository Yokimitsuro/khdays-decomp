#pragma thumb on
/* func_ov016_020819a8 -- tear down the entry's sub-object and clear its "active" flag
 * (bit 2 @+0x12), ov016. */
extern void func_0202ba18(void *sub);
void func_ov016_020819a8(char *obj) {
    func_0202ba18(obj + 0x498);
    *(unsigned short *)(obj + 0x12) &= ~4;
}

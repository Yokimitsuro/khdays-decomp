/* Mission start: fires the owner's cue channels (0: 2, 1: 1) through func_ov022_0209fb60, sets
 * bit 0 of the +0xda8 / +0xf0c bytes whose +1 siblings are set, then runs 020b3a18. */
extern void func_ov022_0209fb60(int a, int b, int c);
extern void func_ov062_020b6218(int a);
extern int *data_ov062_020b80e0;
void func_ov062_020b5cc4(void) {
    int obj = (int)data_ov062_020b80e0;
    func_ov022_0209fb60(obj, 1, 2);
    func_ov022_0209fb60(obj, 0, 1);
    if (*(signed char *)(obj + 0xf0d) != 0)
        *(unsigned char *)(obj + 0xf0c) |= 1;
    if (*(signed char *)(obj + 0xda9) != 0)
        *(unsigned char *)(obj + 0xda8) |= 1;
    func_ov062_020b6218(obj);
}

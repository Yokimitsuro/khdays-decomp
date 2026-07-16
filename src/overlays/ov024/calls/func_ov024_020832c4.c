/* func_ov024_020832c4 -- MobiClip: install the stream-source handler table into `obj`.
 * Five entry points plus the fields they use, all cleared: +0x10 is the only gap in the
 * pointer block (no handler for that slot), and +0x18/+0x1c/+0x28 are the per-instance state
 * the handlers own. */
extern void func_ov024_020831dc(void);
extern void func_ov024_02083238(void);
extern void func_ov024_0208325c(void);
extern void func_ov024_02083280(void);
extern void func_ov024_020832a4(void);

void func_ov024_020832c4(int *obj) {
    obj[0] = (int)func_ov024_020831dc;
    obj[1] = (int)func_ov024_02083238;
    obj[2] = (int)func_ov024_0208325c;
    obj[3] = (int)func_ov024_02083280;
    obj[4] = 0;
    obj[5] = (int)func_ov024_020832a4;
    obj[6] = 0;
    obj[7] = 0;
    obj[10] = 0;
}

/* Latch the pending request once, if the system is idle: only when func_02030788
 * reports free, the mode halfword at +2 is 1 and the latch at +0 is still clear.
 * Sets the latch, posts event 0x11, notifies ov023, sets game flag 0x2484 and
 * marks the session object's +0xe8.
 *
 * data_0204be08 and data_0204be08_params are the SAME address under two names,
 * and that is required, not cosmetic: the ROM's literal pool holds 0x0204be08 in
 * two separate entries, and mwcc emits two only for two distinct symbols. The
 * duplication is in the original too -- one view reads the block as scalar
 * fields, the other hands it to func_02031384 as a parameter buffer, which is
 * what the _params name records. */
extern unsigned short data_0204be08;
extern unsigned short data_0204be08_params;

extern int func_02030788(void);
extern short func_02031384(int a, void *b, int c);
extern void func_ov023_02083aa8(void);
extern void func_020235e8(int flag, int a, int b);

void func_020234e8(void) {
    char *self = *(char **)((char *)&data_0204be08 + 4);

    if (func_02030788() != 0) {
        return;
    }
    if ((&data_0204be08)[1] != 1) {
        return;
    }
    if (data_0204be08 != 0) {
        return;
    }

    data_0204be08 = 1;
    func_02031384(0x11, (void *)&data_0204be08_params, 2);
    func_ov023_02083aa8();
    func_020235e8(0x2484, 1, 1);
    *(int *)(self + 0xe8) = 1;
}

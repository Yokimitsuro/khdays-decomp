/* NONMATCHING: semantics correct. The ROM emits a redundant `orr r1,r5,#0` (a move of param_1)
 * before the shift, which mwcc elides (76B vs 80B); the predicated orreq/orrne order also follows
 * from it. "Our compiler is smarter" class, same as 0207350c / 02055ba4. NOTE: this function is
 * the P6 cursor->action mapping: cmd = (slot<<8) | 7, or | 8 when obj+0x14e0 is set. */
/* func_ov008_0205b720 -- forward a cursor pick to the ov008 scroll widget as an action command.
 * Command = (slot << 8) | action, where action is 7 normally and 8 when the alternate-mode flag
 * (obj+0x14e0) is set. Only runs while a page transition is active (func_ov008_02051028 != 0). */
extern int  func_ov008_02050cd4(void);
extern int  func_ov008_02051028(void);
extern void func_ov008_020566f4(int widget, unsigned int cmd);
extern void func_ov008_0205a8c4(int obj);

void func_ov008_0205b720(int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4) {
    int obj = func_ov008_02050cd4();
    if (func_ov008_02051028() == 0) {
        return;
    }
    {
        unsigned int cmd;
        if (*(int *)(obj + 0x14e0) == 0) {
            cmd = param_1 << 8 | 7;
        } else {
            cmd = param_1 << 8 | 8;
        }
        func_ov008_020566f4(obj + 0x13fc, cmd);
        func_ov008_0205a8c4(obj);
    }
}

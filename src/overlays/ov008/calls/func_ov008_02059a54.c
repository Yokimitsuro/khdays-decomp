/* func_ov008_02059a54 -- if the menu's "busy/locked" flag (bit 5 of *(u16*)(obj+0x5c6)) is set,
 * kick a state transition: set mode 7 (func_ov008_0205714c), clear the active slot
 * (func_ov008_02050970(-1,-1)) and fire a UI event (func_02033b78(0,1)). ov008. One of a
 * 5-member family (02059a54/b14/b5c/ba4/bec) differing in the transition constants. */
extern int  func_ov008_0205714c(int mode);
extern void func_ov008_02050970(int a, int b);
extern void func_02033b78(int a, int b);
extern char *data_ov008_02090f1c;   /* -> menu/status object */

void func_ov008_02059a54(void) {
    if ((((unsigned)*(unsigned short *)(data_ov008_02090f1c + 0x5c6) << 0x1a) >> 0x1f) == 0) {
        return;
    }
    func_ov008_0205714c(7);
    func_ov008_02050970(-1, -1);
    func_02033b78(0, 1);
}

/* func_ov008_02059ab4 -- if menu busy/lock bit 4 of *(u16*)(obj+0x5c6) is set, return; otherwise
 * enter menu mode 1: set mode (func_ov008_0205714c), enable two sub-widgets
 * (func_ov008_02050fe0/02051010), set the active slot (func_ov008_02050970(1,-1)), fire the UI
 * event (func_02033b78(0,1)) and notify (func_ov008_0204ebbc). ov008; 02059a54 family sibling. */
extern int  func_ov008_0205714c(int mode);
extern void func_ov008_02050fe0(int a);
extern void func_ov008_02051010(int a);
extern void func_ov008_02050970(int a, int b);
extern void func_02033b78(int a, int b);
extern void func_ov008_0204ebbc(int a);
extern char *data_ov008_02090f1c;   /* -> menu/status object */

void func_ov008_02059ab4(void) {
    if ((((unsigned)*(unsigned short *)(data_ov008_02090f1c + 0x5c6) << 0x1b) >> 0x1f) != 0) {
        return;
    }
    func_ov008_0205714c(1);
    func_ov008_02050fe0(1);
    func_ov008_02051010(1);
    func_ov008_02050970(1, -1);
    func_02033b78(0, 1);
    func_ov008_0204ebbc(0);
}

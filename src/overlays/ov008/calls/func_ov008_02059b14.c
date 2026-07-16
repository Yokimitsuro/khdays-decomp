/* func_ov008_02059b14 -- if menu busy/lock bit 4 of *(u16*)(obj+0x5c6) is set, return; otherwise
 * kick a state transition: mode 2 (func_ov008_0205714c), slot set (func_ov008_02050970),
 * UI event (func_02033b78(0,1)). ov008. Member of the 02059a54 5-func transition family. */
extern int  func_ov008_0205714c(int mode);
extern void func_ov008_02050970(int a, int b);
extern void func_02033b78(int a, int b);
extern char *data_ov008_02090f1c;   /* -> menu/status object */

void func_ov008_02059b14(void) {
    if ((((unsigned)*(unsigned short *)(data_ov008_02090f1c + 0x5c6) << 0x1b) >> 0x1f) != 0) {
        return;
    }
    func_ov008_0205714c(2);
    func_ov008_02050970(2, -1);
    func_02033b78(0, 1);
}

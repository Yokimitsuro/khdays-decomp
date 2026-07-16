/* func_ov008_0206ebd8 -- disable the whole tag-0xc9..0xdc row block of the mission list
 * (when the global gate data_02090f20 is set). */
extern int  func_ov008_02050c64(void);
extern int  func_ov008_02054788(int list, int tag);
extern void func_ov008_02054ba4(int list, int row, int enabled);
extern int  data_ov008_02090f20;

void func_ov008_0206ebd8(void) {
    if (data_ov008_02090f20 == 0) {
        return;
    }
    {
        int list = func_ov008_02050c64();
        int tag = 0xc9;
        do {
            int row = func_ov008_02054788(list, tag);
            func_ov008_02054ba4(list, row, 0);
            tag = tag + 1;
        } while (tag <= 0xdc);
    }
}

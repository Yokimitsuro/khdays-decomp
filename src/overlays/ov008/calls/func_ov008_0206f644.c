/* func_ov008_0206f644 -- when the menu is on page state 1, enable the mission list's tag-0x47 row.
 * Gets the menu object (func_ov008_02050cec) and its list (func_ov008_02050c64); bails unless the
 * global gate data_02090f20 is set and obj+0x44 == 1; then enables the row (func_ov008_02054ba4). */
extern int  func_ov008_02050cec(void);
extern int  func_ov008_02050c64(void);
extern int  func_ov008_02054788(int list, int tag);
extern void func_ov008_02054ba4(int list, int row, int enabled);
extern int  data_ov008_02090f20;

void func_ov008_0206f644(void) {
    int obj = func_ov008_02050cec();
    int list = func_ov008_02050c64();
    if (data_ov008_02090f20 == 0) {
        return;
    }
    if (*(int *)(obj + 0x44) != 1) {
        return;
    }
    {
        int row = func_ov008_02054788(list, 0x47);
        func_ov008_02054ba4(list, row, 1);
    }
}

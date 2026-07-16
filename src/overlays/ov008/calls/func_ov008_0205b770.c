/* func_ov008_0205b770 -- feed input param_1 to the ov008 menu's scroll widget when it is idle.
 * Gets the menu object; bails if a page transition is running (func_ov008_02051028) or the widget
 * is disabled (func_ov008_02050ff8 == 0); otherwise forwards to func_ov008_020566f4 (obj+0x13fc)
 * and refreshes (func_ov008_0205a8c4). */
extern int  func_ov008_02050cd4(void);
extern int  func_ov008_02051028(void);
extern int  func_ov008_02050ff8(void);
extern void func_ov008_020566f4(int widget, unsigned int input);
extern void func_ov008_0205a8c4(int obj);

void func_ov008_0205b770(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4) {
    int obj = func_ov008_02050cd4();
    if (func_ov008_02051028() != 0) {
        return;
    }
    if (func_ov008_02050ff8() == 0) {
        return;
    }
    func_ov008_020566f4(obj + 0x13fc, param_1);
    func_ov008_0205a8c4(obj);
}

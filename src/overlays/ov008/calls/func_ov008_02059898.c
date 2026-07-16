/* func_ov008_02059898 -- ov008 character menu confirm. If the roster cursor (func_020235d0 slot 9)
 * is below 8 it is an empty slot: just fire UI event 4. Otherwise commit the pick
 * (func_ov008_02058df0(obj, 2)) and fire UI event 1. */
extern int  func_ov008_02050cd4(void);
extern unsigned int func_020235d0(int a, int b);
extern void func_02033b78(int a, int b);
extern void func_ov008_02058df0(int obj, int arg);

void func_ov008_02059898(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4) {
    int obj = func_ov008_02050cd4();
    unsigned int slot = func_020235d0(0, 9);
    if (slot <= 7) {
        func_02033b78(0, 4);
        return;
    }
    func_ov008_02058df0(obj, 2);
    func_02033b78(0, 1);
}

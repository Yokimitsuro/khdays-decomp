/* func_ov008_02073fe8 -- confirm-guard for a second ov008 menu page (same shape as 02078214).
 * Bails if mid-slide (obj+0x40 set while obj+0x44 clear) or nothing pending (obj+0x4f8 clear);
 * arms the selection if not armed (obj+0x4fc clear) then runs the confirm (func_ov008_02071ebc). */
extern int  func_ov008_02050cec(void);
extern void func_ov008_02071d40(int obj, int arg);
extern void func_ov008_02071ebc(int obj);

void func_ov008_02073fe8(void) {
    int obj = func_ov008_02050cec();
    if (*(int *)(obj + 0x40) != 0 && *(int *)(obj + 0x44) == 0) {
        return;
    }
    if (*(int *)(obj + 0x4f8) == 0) {
        return;
    }
    if (*(int *)(obj + 0x4fc) == 0) {
        func_ov008_02071d40(obj, 1);
    }
    func_ov008_02071ebc(obj);
}

/* func_ov008_02078214 -- confirm-guard for the ov008 mission menu.
 * Gets the menu object (func_ov008_02050cec); bails if it is mid-slide (obj+0x150 set while
 * obj+0x154 clear) or has no pending selection (obj+0x180 clear). If the selection is not yet
 * armed (obj+0x184 clear), arm it (func_ov008_02076e80(.,1)); then run the confirm
 * (func_ov008_020745c4). */
extern int  func_ov008_02050cec(void);
extern void func_ov008_02076e80(int obj, int arg);
extern void func_ov008_020745c4(void);

void func_ov008_02078214(void) {
    int obj = func_ov008_02050cec();
    if (*(int *)(obj + 0x150) != 0 && *(int *)(obj + 0x154) == 0) {
        return;
    }
    if (*(int *)(obj + 0x180) == 0) {
        return;
    }
    if (*(int *)(obj + 0x184) == 0) {
        func_ov008_02076e80(obj, 1);
    }
    func_ov008_020745c4();
}

/* func_ov008_02061ee8 -- per-frame update of an ov008 grid cell: runs the base tick
 * (func_ov008_02061e64), then if a hit entry is resolved (func_ov008_0205fdac) applies its two
 * effects (func_ov008_02060850/020609e4); finally advances the cell's animator (obj+0xac). */
extern void func_ov008_02061e64(int obj, unsigned int a, unsigned int b, unsigned int c);
extern int  func_ov008_0205fdac(int obj, unsigned int a, unsigned int b, unsigned int c);
extern void func_ov008_02060850(int obj, int entry);
extern void func_ov008_020609e4(int obj, int entry);
extern void func_020300f8(int animator);

void func_ov008_02061ee8(int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4) {
    int entry;
    func_ov008_02061e64(param_1, param_2, param_3, param_4);
    entry = func_ov008_0205fdac(param_1, param_2, param_3, param_4);
    if (entry != 0) {
        func_ov008_02060850(param_1, entry);
        func_ov008_020609e4(param_1, entry);
    }
    func_020300f8(param_1 + 0xac);
}

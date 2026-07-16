/* func_ov006_0204fdac -- Mission Mode: leave the current sub-menu, ov105 variant.
 * Same shape as func_ov006_0204fd68 but hands off to func_ov006_0204ed64 and finishes with the
 * ov105 teardown (func_ov105_020bf928) instead of the ov006 one. */
extern void func_ov105_020bf8c8(int a);
extern void func_02023a44(int obj, int next);
extern void func_ov105_020bf928(void);
extern void func_ov006_0204ed64(void);
extern int  data_ov006_020565e4;

void func_ov006_0204fdac(void) {
    func_ov105_020bf8c8(0);
    func_02023a44(*(int *)((int)&data_ov006_020565e4 + 4), (int)func_ov006_0204ed64);
    func_ov105_020bf928();
}

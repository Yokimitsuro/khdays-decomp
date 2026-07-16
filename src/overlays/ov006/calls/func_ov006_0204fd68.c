/* func_ov006_0204fd68 -- Mission Mode: leave the current sub-menu back to the previous screen.
 * Silences the ov105 sound channel, hands the scene object (data_ov006_020565e4[1]) over to
 * func_02023a44 with func_ov006_0204ed2c as its next state, then runs the shared teardown. */
extern void func_ov105_020bf8c8(int a);
extern void func_02023a44(int obj, int next);
extern void func_ov006_0204dbb4(void);
extern void func_ov006_0204ed2c(void);
extern int  data_ov006_020565e4;

void func_ov006_0204fd68(void) {
    func_ov105_020bf8c8(0);
    func_02023a44(*(int *)((int)&data_ov006_020565e4 + 4), (int)func_ov006_0204ed2c);
    func_ov006_0204dbb4();
}

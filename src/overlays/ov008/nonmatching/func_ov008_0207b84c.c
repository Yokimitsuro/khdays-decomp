/* NONMATCHING: correct; register-allocation tie (+/-4B). The ROM keeps the g-array address in
 * r2 and loads g[0] into r0, reading g[1] via [r2,#4]; our mwcc reuses r2 for g[0]. Lazy help
 * sub-scene create/re-enter. */
/* func_ov008_0207b84c -- lazily create or re-enter the menu's help sub-scene, ov008.
 * On first call the help sub-scene object is instantiated from its class descriptor
 * (data_ov008_02090bb0) and cached in slot g[1]. On later calls it bumps the help object's
 * frame counter (base+0x4f2) and re-runs its per-frame step (func_02023a44 with the state fn
 * func_ov008_0207947c). */
extern int  func_02023930(void *desc, int arg);
extern void func_02023a44(int inst, void *fn);
extern int  data_ov008_02090f24[];
extern char data_ov008_02090bb0[];
extern void func_ov008_0207947c(void);

void func_ov008_0207b84c(int arg) {
    int *g = data_ov008_02090f24;
    if (g[1] == 0) {
        g[1] = func_02023930(data_ov008_02090bb0, arg);
        return;
    }
    *(unsigned short *)(g[0] + 0x4f2) = *(unsigned short *)(g[0] + 0x4f2) + 1;
    func_02023a44(g[1], (void *)func_ov008_0207947c);
}

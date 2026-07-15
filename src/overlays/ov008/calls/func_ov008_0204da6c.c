/* func_ov008_0204da6c -- update the menu cursor sprite, ov008. Reads the cursor's target
 * cell (func_ov008_0207b7b4; <0 = hidden, skip), then drives the cursor object
 * (*(heap+0x5044)) in the scene object manager (heap+0x60c): set frame to the cell
 * (func_020325ec), refresh (func_020326cc), reset scale to 1.0 (func_0203257c), re-add
 * (func_020324ac) and commit (func_0203253c). */
extern char *data_ov008_02090f00;
extern int  func_ov008_0207b7b4(void);
extern void func_020325ec(void *mgr, void *obj, int frame);
extern void func_020326cc(void *mgr, void *obj);
extern void func_0203257c(void *mgr, void *obj, int *scale);
extern void func_020324ac(void *mgr, void *obj);
extern void func_0203253c(void *mgr);
void func_ov008_0204da6c(void) {
    int cell = func_ov008_0207b7b4();
    if (cell < 0) {
        return;
    }
    func_020325ec(data_ov008_02090f00 + 0x60c, *(void **)(data_ov008_02090f00 + 0x5044),
                  (unsigned short)cell);
    func_020326cc(data_ov008_02090f00 + 0x60c, *(void **)(data_ov008_02090f00 + 0x5044));
    {
        int scale[2];
        scale[0] = 0x8000;
        scale[1] = 0x8000;
        func_0203257c(data_ov008_02090f00 + 0x60c, *(void **)(data_ov008_02090f00 + 0x5044), scale);
    }
    func_020324ac(data_ov008_02090f00 + 0x60c, *(void **)(data_ov008_02090f00 + 0x5044));
    func_0203253c(data_ov008_02090f00 + 0x60c);
}

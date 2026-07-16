/* func_ov008_0207c4a4 -- test whether the title menu confirm should fire, ov006.
 * When the title is idle (base+0x20 == 0), checks the currently highlighted option
 * (func_ov008_0207b2b0 on the 0-based cursor from base+0x38); when active, checks the generic
 * confirm (func_ov008_0207b1cc). Either success selects the confirm state fn
 * (func_ov008_0207c518). Always refreshes the cursor sprite (func_ov008_0208187c(0xff)) and, on
 * confirm, plays the decide SFX (func_ov008_020817c4(2,0)). Returns the selected state (or 0). */
extern int  func_ov008_0207b1cc(void);
extern int  func_ov008_0207b2b0(int option);
extern void func_ov008_0208187c(int a);
extern void func_ov008_020817c4(int a, int b, int c);
extern int  data_ov008_02090fa0;
extern void func_ov008_0207c518(void);

int func_ov008_0207c4a4(void) {
    int result = 0;
    if (*(int *)(data_ov008_02090fa0 + 0x20) != 0) {
        if (func_ov008_0207b1cc() != 0) {
            result = (int)func_ov008_0207c518;
        }
    } else {
        if (func_ov008_0207b2b0((*(int *)(data_ov008_02090fa0 + 0x38) - 1U) & 0xff) != 0) {
            result = (int)func_ov008_0207c518;
        }
    }
    func_ov008_0208187c(-1);
    if (result != 0) {
        func_ov008_020817c4(2, 0, 0);
    }
    return result;
}

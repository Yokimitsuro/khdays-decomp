/* NONMATCHING: correct; scheduling tie only -- the ROM reads cursor[0] then cursor[1] (r2,r1)
 * before storing; our mwcc reverses the two independent loads (same class as func_ov008_0204ec34).
 * Prime menu sub-scene from cursor + difficulty. */
/* func_ov008_0205714c -- prime the menu sub-scene from the current cursor + a difficulty, ov008.
 * Snapshots the current cursor triple (func_ov008_0204ed20), and for a negative arg clears the
 * sub-scene (func_ov008_0204ec34(0)); otherwise selects page arg (func_ov008_02050e2c), stamps
 * the difficulty byte into the triple's second short, and hands the triple to the sub-scene. */
extern int   func_02030788(void);
extern unsigned short *func_ov008_0204ed20(void);
extern void  func_ov008_0204ec34(unsigned short *init);
extern void  func_ov008_02050e2c(int page);

void func_ov008_0205714c(int arg) {
    unsigned short init[3];
    unsigned short *cur;
    func_02030788();
    cur = func_ov008_0204ed20();
    {
        unsigned short a = cur[0];
        unsigned short b = cur[1];
        unsigned short c = cur[2];
        init[0] = a;
        init[1] = b;
        init[2] = c;
    }
    if (arg < 0) {
        func_ov008_0204ec34(0);
        return;
    }
    func_ov008_02050e2c(arg);
    *((char *)init + 3) = (char)arg;
    func_ov008_0204ec34(init);
}

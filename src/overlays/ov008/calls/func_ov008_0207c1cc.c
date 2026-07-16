/* func_ov008_0207c1cc -- main-menu tick, returns the next scene state (0 = stay).
 * While the menu is still opening (func_ov008_0207bc6c) it only waits for the open animation
 * to finish and then advances to func_ov008_0207d5d8. Once open, a committed selection
 * (func_ov008_0207b14c) clears the 8-byte selection block at OBJ+0x38, stops the menu tweens
 * and the cursor, and advances to func_ov008_0207c248.
 *
 * PROVENANCE: byte-identical twin of func_ov006_020502e4 -- same code, this overlay's own
 * globals, propagated mechanically and verified byte-exact.
 * The scene-identity phrasing that came with the twin source (Mission Mode / char select /
 * ov025 panel) is the REP's, NOT established for ov008, so it was removed rather than
 * carried over. What IS measured: ov008's own strings include UI/mlt/res.p2 (the same pack
 * ov006 loads) plus UI/cm/*.p2 and ba/ch/*, so resource detail naming those is sound; the
 * scene label is not. The offsets and logic below are this function's -- the code is
 * byte-identical to the rep.
 */
extern int  func_ov008_0207bc6c(void);
extern int  func_ov008_0207bc80(void);
extern int  func_ov008_0207b14c(void);
extern void MI_CpuFill8(void *dst, int data, unsigned int size);
extern void func_ov008_020817c4(int a, int b, int c);
extern void func_ov008_02081d58(int a);
extern void func_ov008_0207d5d8(void);
extern void func_ov008_0207c248(void);
extern int  data_ov008_02090fa0;

void *func_ov008_0207c1cc(void) {
    void *next = 0;
    if (func_ov008_0207bc6c() == 0) {
        if (func_ov008_0207bc80() != 0) {
            return (void *)func_ov008_0207d5d8;
        }
        return next;
    }
    if (func_ov008_0207b14c() != 0) {
        void *sel = *(char **)&data_ov008_02090fa0 + 0x38;
        /* `clear` is next's still-zero value: the ROM keeps both in the same callee-saved
         * register and reloads it with func_ov008_0207c248 before the fill call, so the
         * capture-then-reassign order below is what reproduces its schedule. */
        int clear = (int)next;
        next = (void *)func_ov008_0207c248;
        MI_CpuFill8(sel, clear, 8);
        func_ov008_020817c4(0, 0, 0);
        func_ov008_02081d58(0);
    }
    return next;
}

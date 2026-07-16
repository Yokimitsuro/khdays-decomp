/* func_ov008_02078954 -- start the menu's close/collapse slide, ov008.
 * Unless already closed (func_ov008_0207890c set), kicks a scroll animation on the panel
 * (rec+0x10) from rec+0x2c to -0x10000 over 100 units, commits it, raises the closed flag
 * (rec+0x1f4=1) and sets the panel state to closing (rec+0x1f8=2). */
extern int  func_ov008_02050cec(void);
extern int  func_ov008_0207890c(void);
extern void func_02035fb0(unsigned int *anim, int a, unsigned int from, int to, int dur);
extern void func_02035ffc(int anim);

void func_ov008_02078954(void) {
    int rec = func_ov008_02050cec();
    if (func_ov008_0207890c() == 0) {
        func_02035fb0((unsigned int *)(rec + 0x10), 0, *(unsigned int *)(rec + 0x2c), -0x10000, 100);
        func_02035ffc(rec + 0x10);
        *(int *)(rec + 0x1f4) = 1;
        *(int *)(rec + 0x1f8) = 2;
    }
}

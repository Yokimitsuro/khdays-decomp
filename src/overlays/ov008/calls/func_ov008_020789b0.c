/* func_ov008_020789b0 -- start the menu's open/expand slide, ov008.
 * Unless already open (func_ov008_0207890c set and rec+0x1f4 clear), kicks a scroll animation on
 * the panel (rec+0x10) from rec+0x2c to 0 over 100 units, commits it, clears the closed flag
 * (rec+0x1f4) and raises the visible flag (rec+0x1f8). */
extern int  func_ov008_02050cec(void);
extern int  func_ov008_0207890c(void);
extern void func_02035fb0(unsigned int *anim, int a, unsigned int from, int to, int dur);
extern void func_02035ffc(int anim);

void func_ov008_020789b0(void) {
    int rec = func_ov008_02050cec();
    if (func_ov008_0207890c() != 0 && *(int *)(rec + 0x1f4) == 0) {
        return;
    }
    func_02035fb0((unsigned int *)(rec + 0x10), 0, *(unsigned int *)(rec + 0x2c), 0, 100);
    func_02035ffc(rec + 0x10);
    *(int *)(rec + 0x1f4) = 0;
    *(int *)(rec + 0x1f8) = 1;
}

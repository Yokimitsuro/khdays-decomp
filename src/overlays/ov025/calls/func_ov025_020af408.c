/* func_ov025_020af408 -- start the menu's open/expand slide, ov008.
 * Unless already open (func_ov025_020af364 set and rec+0x1f4 clear), kicks a scroll animation on
 * the panel (rec+0x10) from rec+0x2c to 0 over 100 units, commits it, clears the closed flag
 * (rec+0x1f4) and raises the visible flag (rec+0x1f8). */
extern int  func_ov025_02084b14(void);
extern int  func_ov025_020af364(void);
extern void func_02035fb0(unsigned int *anim, int a, unsigned int from, int to, int dur);
extern void func_02035ffc(int anim);

void func_ov025_020af408(void) {
    int rec = func_ov025_02084b14();
    if (func_ov025_020af364() != 0 && *(int *)(rec + 0x1f4) == 0) {
        return;
    }
    func_02035fb0((unsigned int *)(rec + 0x10), 0, *(unsigned int *)(rec + 0x2c), 0, 100);
    func_02035ffc(rec + 0x10);
    *(int *)(rec + 0x1f4) = 0;
    *(int *)(rec + 0x1f8) = 1;
}

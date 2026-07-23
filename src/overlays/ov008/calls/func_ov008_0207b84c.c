/* Arm the wireless callback: if the session handle at +4 is still empty, open it from the
 * descriptor block and stop. Otherwise bump the retry counter at +0x4f2 of the session object and
 * re-register func_ov008_0207947c on the existing handle.
 *
 * Matched byte-exact 2026-07-23, closing an old park. The park held the global in a local, which
 * makes mwcc park it in a callee-saved register across the call; the ROM re-materialises the pool
 * address instead, so the global has to be referenced directly every time. The last piece is a
 * CSE break: the guard and the final argument read the SAME word, and mwcc folds them into one
 * load unless they are spelled differently -- the ROM reloads it, because the first load's
 * register is clobbered by the session pointer in between. */
extern int  func_02023930(void *desc, int arg);
extern void func_02023a44(int inst, void *fn);
extern int  data_ov008_02090f24[];
extern char data_ov008_02090bb0[];
extern void func_ov008_0207947c(void);

void func_ov008_0207b84c(int arg) {
    if (data_ov008_02090f24[1] == 0) {
        data_ov008_02090f24[1] = func_02023930(data_ov008_02090bb0, arg);
        return;
    }
    *(unsigned short *)(data_ov008_02090f24[0] + 0x4f2) =
        *(unsigned short *)(data_ov008_02090f24[0] + 0x4f2) + 1;
    func_02023a44(*(int *)((char *)data_ov008_02090f24 + 4), (void *)func_ov008_0207947c);
}

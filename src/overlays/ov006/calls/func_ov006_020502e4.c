/* func_ov006_020502e4 -- Mission Mode: main-menu tick, returns the next scene state (0 = stay).
 * While the menu is still opening (func_ov006_0204fe88) it only waits for the open animation
 * to finish and then advances to func_ov006_02051884. Once open, a committed selection
 * (func_ov006_0204f3f0) clears the 8-byte selection block at OBJ+0x38, stops the menu tweens
 * and the cursor, and advances to func_ov006_02050360. */
extern int  func_ov006_0204fe88(void);
extern int  func_ov006_0204fe9c(void);
extern int  func_ov006_0204f3f0(void);
extern void MI_CpuFill8(void *dst, int data, unsigned int size);
extern void func_ov006_02055a54(int a, int b, int c);
extern void func_ov006_02055fe8(int a);
extern void func_ov006_02051884(void);
extern void func_ov006_02050360(void);
extern int  data_ov006_02056660;

void *func_ov006_020502e4(void) {
    void *next = 0;
    if (func_ov006_0204fe88() == 0) {
        if (func_ov006_0204fe9c() != 0) {
            return (void *)func_ov006_02051884;
        }
        return next;
    }
    if (func_ov006_0204f3f0() != 0) {
        void *sel = *(char **)&data_ov006_02056660 + 0x38;
        /* `clear` is next's still-zero value: the ROM keeps both in the same callee-saved
         * register and reloads it with func_ov006_02050360 before the fill call, so the
         * capture-then-reassign order below is what reproduces its schedule. */
        int clear = (int)next;
        next = (void *)func_ov006_02050360;
        MI_CpuFill8(sel, clear, 8);
        func_ov006_02055a54(0, 0, 0);
        func_ov006_02055fe8(0);
    }
    return next;
}

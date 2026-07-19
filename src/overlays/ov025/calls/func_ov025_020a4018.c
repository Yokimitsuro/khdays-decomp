extern void func_ov025_020a3848(char *self);
extern void func_ov025_02089884(char *p);
extern void func_0202ffbc(char *p);
extern void func_ov025_02084f08(int id);
extern int func_ov025_020a0f28(void);
extern int func_ov025_02084a64(void);
extern int func_ov025_020895b8(int a);
extern int func_ov025_02084a8c(int a);
extern void func_ov025_020883a0(int a);
extern void func_ov025_020883d4(int a);
extern void func_ov025_02084b78(int node);
extern int data_ov025_020b575c;

/* Scene teardown: releases the sub-allocators, drops the three fixed resources plus the current
 * one, unwinds the active object and clears the sub-engine's window registers. */
void func_ov025_020a4018(char *self) {
    int obj;
    func_ov025_020a3848(self);
    func_ov025_02089884(self + 0x58);
    func_0202ffbc(self + 0x64);
    func_0202ffbc(self + 0xa0);
    func_0202ffbc(self + 0xdc);
    func_0202ffbc(self + 0x118);
    func_0202ffbc(self + 0x154);
    func_0202ffbc(self + 0x190);
    func_ov025_02084f08(0x1c);
    func_ov025_02084f08(0x15);
    func_ov025_02084f08(0x13);
    func_ov025_02084f08(func_ov025_020a0f28());
    obj = func_ov025_02084a8c(func_ov025_020895b8(func_ov025_02084a64()));
    func_ov025_020883a0(obj);
    func_ov025_020883d4(obj);
    func_ov025_02084b78(*(int *)(self + 0x23c));
    {
        volatile int *win = (volatile int *)0x04001010;
        win[0] = 0;
        win[1] = 0;
        win[2] = 0;
        win[3] = 0;
        data_ov025_020b575c = 0;
    }
}

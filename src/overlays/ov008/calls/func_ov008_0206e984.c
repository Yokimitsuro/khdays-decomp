extern void func_ov008_0206e1b4(char *self);
extern void func_ov008_02055c74(char *p);
extern void func_0202ffbc(char *p);
extern void func_ov008_020510f8(int id);
extern int func_ov008_0206b6e4(void);
extern int func_ov008_02050c3c(void);
extern int func_ov008_020559a8(int a);
extern int func_ov008_02050c64(int a);
extern void func_ov008_020546ec(int a);
extern void func_ov008_02054720(int a);
extern void func_ov008_02050d50(int node);
extern int data_ov008_02090f20;

/* Scene teardown: releases the sub-allocators, drops the three fixed resources plus the current
 * one, unwinds the active object and clears the sub-engine's window registers. */
void func_ov008_0206e984(char *self) {
    int obj;
    func_ov008_0206e1b4(self);
    func_ov008_02055c74(self + 0x58);
    func_0202ffbc(self + 0x64);
    func_0202ffbc(self + 0xa0);
    func_0202ffbc(self + 0xdc);
    func_0202ffbc(self + 0x118);
    func_0202ffbc(self + 0x154);
    func_0202ffbc(self + 0x190);
    func_ov008_020510f8(0x1c);
    func_ov008_020510f8(0x15);
    func_ov008_020510f8(0x13);
    func_ov008_020510f8(func_ov008_0206b6e4());
    obj = func_ov008_02050c64(func_ov008_020559a8(func_ov008_02050c3c()));
    func_ov008_020546ec(obj);
    func_ov008_02054720(obj);
    func_ov008_02050d50(*(int *)(self + 0x23c));
    {
        volatile int *win = (volatile int *)0x04001010;
        win[0] = 0;
        win[1] = 0;
        win[2] = 0;
        win[3] = 0;
        data_ov008_02090f20 = 0;
    }
}

extern void func_0202ffbc(char *p);
extern void func_ov008_02055c74(char *p);
extern void func_ov008_0205658c(char *p);
extern int func_ov008_02050c28(void);
extern int func_ov008_02050c3c(void);
extern int func_ov008_02050c54(void);
extern int func_ov008_02050c64(void);
extern void func_ov008_020559a8(int a);
extern void func_ov008_020546ec(int a);
extern void func_ov008_02054720(int a);
extern void func_ov008_0205c458(char *p);

/* Field teardown: releases the four sub-allocators and the layout, then unwinds all four cached
 * objects and hands the scene block to the shared unloader. */
void func_ov008_0205b398(char *self) {
    int a;
    int b;
    int c;
    int d;
    func_0202ffbc(self + 0x420 + 0x1000);
    func_0202ffbc(self + 0x5c + 0x1400);
    func_0202ffbc(self + 0x98 + 0x1400);
    func_ov008_02055c74(self + 0xf4 + 0x1400);
    func_ov008_0205658c(self + 0x3fc + 0x1000);
    a = func_ov008_02050c28();
    b = func_ov008_02050c3c();
    c = func_ov008_02050c54();
    d = func_ov008_02050c64();
    func_ov008_020559a8(a);
    func_ov008_020559a8(b);
    func_ov008_020546ec(c);
    func_ov008_02054720(c);
    func_ov008_020546ec(d);
    func_ov008_02054720(d);
    func_ov008_0205c458(self + 4);
}

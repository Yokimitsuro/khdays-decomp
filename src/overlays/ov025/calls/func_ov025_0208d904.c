extern void func_0202ffbc(char *p);
extern void func_ov025_02089884(char *p);
extern void func_ov025_0208a19c(char *p);
extern int func_ov025_02084a50(void);
extern int func_ov025_02084a64(void);
extern int func_ov025_02084a7c(void);
extern int func_ov025_02084a8c(void);
extern void func_ov025_020895b8(int a);
extern void func_ov025_020883a0(int a);
extern void func_ov025_020883d4(int a);
extern void func_ov025_0208e9ec(char *p);

/* Field teardown: releases the four sub-allocators and the layout, then unwinds all four cached
 * objects and hands the scene block to the shared unloader. */
void func_ov025_0208d904(char *self) {
    int a;
    int b;
    int c;
    int d;
    func_0202ffbc(self + 0x420 + 0x1000);
    func_0202ffbc(self + 0x5c + 0x1400);
    func_0202ffbc(self + 0x98 + 0x1400);
    func_ov025_02089884(self + 0xf4 + 0x1400);
    func_ov025_0208a19c(self + 0x3fc + 0x1000);
    a = func_ov025_02084a50();
    b = func_ov025_02084a64();
    c = func_ov025_02084a7c();
    d = func_ov025_02084a8c();
    func_ov025_020895b8(a);
    func_ov025_020895b8(b);
    func_ov025_020883a0(c);
    func_ov025_020883d4(c);
    func_ov025_020883a0(d);
    func_ov025_020883d4(d);
    func_ov025_0208e9ec(self + 4);
}

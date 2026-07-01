extern void func_02005414(void);
extern void func_020054b0(void);
extern void func_020030e4(void);
extern void func_0200d608(void);
extern void func_0200e18c(int a, int b);
extern void func_02005630(void);
extern void func_0201e374(int a);
extern void func_0201e3cc(int a);
extern void func_02011594(void *p, int n);
extern void func_02000f1c(void);
extern void OS_EnableIrqMask(int mask);
extern void func_ov001_0204cf5c(void);
extern void func_ov001_0204cac0(void);
extern void func_ov001_0204cbb4(void);
extern void func_ov001_0204cb6c(void);
extern void func_ov001_0204cccc(void);
extern int data_020422b8;
extern int data_0204be24;

void func_ov001_0204cd7c(void) {
    volatile unsigned short *reg304 = (volatile unsigned short *)0x04000304;
    volatile unsigned int *reg1000 = (volatile unsigned int *)0x04001000;
    volatile unsigned short *reg208 = (volatile unsigned short *)0x04000208;
    unsigned short dummy;

    func_02005414();
    *reg304 = (unsigned short)((*reg304 & ~0x20e) | 0x20e);
    data_020422b8 = 1;
    func_020054b0();
    func_020030e4();
    func_0200d608();
    func_0200e18c(0x500, 0x2400);
    func_02005630();
    *reg1000 &= ~0x10000;
    func_0201e374(0x10);
    func_0201e3cc(0x10);
    func_02011594(&data_0204be24, 0x20);
    func_02000f1c();
    OS_EnableIrqMask(0x40000);
    dummy = *reg208;
    *reg208 = 1;
    func_ov001_0204cf5c();
    func_ov001_0204cac0();
    func_ov001_0204cbb4();
    func_ov001_0204cb6c();
    func_ov001_0204cccc();
}

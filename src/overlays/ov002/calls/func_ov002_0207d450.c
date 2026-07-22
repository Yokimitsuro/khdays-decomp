/* Read three operands out of the script arguments -- at +0, +8 and +0x10 -- and
 * drive the widget with them. The first two are narrowed on the way in (byte and
 * halfword, hence the lsl/lsr pairs rather than an `and`); the third is passed
 * whole to func_ov002_0207a700 alongside whatever the first call returns.
 * Always reports 1. */
extern int func_02021980(void *self, void *arg);
extern int func_ov002_0207679c(unsigned char a, unsigned short b);
extern void func_ov002_0207a700(int handle, int c);

int func_ov002_0207d450(void *self, char *args) {
    int a = func_02021980(self, args);
    int b = func_02021980(self, args + 8);
    int c = func_02021980(self, args + 0x10);

    func_ov002_0207a700(func_ov002_0207679c((unsigned char)a, (unsigned short)b), c);
    return 1;
}

/* Script opcode: resolve four operands and drive func_ov002_02072194 with them,
 * the third narrowed to an unsigned halfword and the fourth to a signed byte,
 * with -1 as the fifth (stack) argument. Reports 1. */
extern int func_02021980(void *self, void *arg);
extern void func_ov002_02072194(int a, int b, unsigned short c, signed char d, int e);

int func_ov002_020750bc(void *self, char *args) {
    int a = func_02021980(self, args);
    int b = func_02021980(self, args + 8);
    int c = func_02021980(self, args + 0x10);
    int d = func_02021980(self, args + 0x18);

    func_ov002_02072194(a, b, (unsigned short)c, (signed char)d, -1);
    return 1;
}

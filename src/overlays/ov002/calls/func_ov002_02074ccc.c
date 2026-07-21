extern int func_02021980(int vm, unsigned short *pc);
extern int func_02020400(int value, int scale);
extern void func_ov002_0206d9d0(int value);
/* Script op: read an operand, scale it as a 16.16 fixed-point fraction of 0x168, and publish the
 * u16 result into the root context. */
int func_ov002_02074ccc(int vm, unsigned short *pc) {
    int v = func_02021980(vm, pc);
    func_ov002_0206d9d0((unsigned short)func_02020400(v << 0x10, 0x168));
    return 1;
}

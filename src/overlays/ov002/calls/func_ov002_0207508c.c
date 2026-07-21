extern int func_02021980(int vm, unsigned short *pc);
extern void func_ov002_0206bbb8(int slot, int a, int b);
/* Script op: skip the first operand, read the next two, and invoke the handler with slot 0. */
int func_ov002_0207508c(int vm, unsigned short *pc) {
    int a, b;
    func_02021980(vm, pc);
    a = func_02021980(vm, pc + 4);
    b = func_02021980(vm, pc + 8);
    func_ov002_0206bbb8(0, a, b);
    return 1;
}

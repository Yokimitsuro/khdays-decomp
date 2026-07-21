extern int func_02021980(int vm, unsigned short *pc);
extern void func_ov002_0206b070(unsigned int negated, unsigned int arg);
/* Script op: read two operands and invoke the handler with the first inverted to a boolean. */
int func_ov002_020746dc(int vm, unsigned short *pc) {
    int a = func_02021980(vm, pc);
    unsigned int b = func_02021980(vm, pc + 4);
    func_ov002_0206b070((unsigned int)(a == 0), b);
    return 1;
}

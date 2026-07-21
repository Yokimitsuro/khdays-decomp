extern int func_02021980(int vm, unsigned short *pc);
extern unsigned int *func_02021948(int vm, unsigned short *pc);
extern short func_02020a9c(void);
extern void func_ov023_02083f1c(int a, unsigned int *b);
/* Script op: read an operand and a resolved pointer; only act when the current opcode is 0xc. */
int func_ov023_02086eb4(int vm, unsigned short *pc) {
    int a = func_02021980(vm, pc);
    unsigned int *p = func_02021948(vm, pc + 4);
    if (func_02020a9c() != 0xc) {
        return 1;
    }
    func_ov023_02083f1c(a, p);
    return 1;
}

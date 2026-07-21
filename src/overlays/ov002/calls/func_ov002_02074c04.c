extern int func_02021980(int vm, unsigned short *pc);
extern void func_ov002_020726f4(int a, int b, unsigned int flag);
/* Script op: read three operands and invoke the handler with the third reduced to a boolean. */
int func_ov002_02074c04(int vm, unsigned short *pc) {
    int a = func_02021980(vm, pc);
    int b = func_02021980(vm, pc + 4);
    int c = func_02021980(vm, pc + 8);
    func_ov002_020726f4(a, b, (unsigned int)(c != 0));
    return 1;
}

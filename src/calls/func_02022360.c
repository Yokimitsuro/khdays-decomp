/* func_02022360 -- script VM command: read the operand, arm the "waiting" flag at data_020425e8
 * (-1 = waiting) and hand the operand to func_020336a4. Always reports 1 (finished).
 * The flag's address doubles as the call's second argument, which is why the ROM sets it up once. */
extern int func_02021980(void *vm, void *op);
extern void func_020336a4(int a, void *b);
extern char data_020425e8;

int func_02022360(void *vm, void *op) {
    int r = func_02021980(vm, op);
    data_020425e8 = -1;
    func_020336a4(r, &data_020425e8);
    return 1;
}

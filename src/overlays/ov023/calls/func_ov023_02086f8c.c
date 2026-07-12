/* Resolve the argument, register it (slot 1) via ov023_02089ccc, notify 02033bb4 for id 0x2da
 * and report success. */
extern int func_02021980(int a);
extern void func_ov023_02089ccc(int a, int b);
extern void func_02033bb4(int a, int b);
int func_ov023_02086f8c(int param_1) {
    func_ov023_02089ccc(1, func_02021980(param_1));
    func_02033bb4(0x2da, 0);
    return 1;
}

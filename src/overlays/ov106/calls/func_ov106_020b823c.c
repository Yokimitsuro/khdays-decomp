/* Resolve the argument, register it (slot 0) via ov106_020b8a24, notify 02033bb4 for id 0x2da
 * with flag 5 and report success. */
extern int func_02021980(int a);
extern void func_ov106_020b8a24(int a, int b);
extern void func_02033bb4(int a, int b, int c);
int func_ov106_020b823c(int param_1) {
    func_ov106_020b8a24(0, func_02021980(param_1));
    func_02033bb4(0x2da, 0, 5);
    return 1;
}

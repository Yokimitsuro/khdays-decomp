/* Resolve the argument, register it (slot 1) via ov106_020b8a24, notify 02033b24 for id 0x2da
 * and report success. */
extern int func_02021980(int a);
extern void func_ov106_020b8a24(int a, int b);
extern void func_02033b24(int a, int b);
int func_ov106_020b821c(int param_1) {
    func_ov106_020b8a24(1, func_02021980(param_1));
    func_02033b24(0x2da, 0);
    return 1;
}

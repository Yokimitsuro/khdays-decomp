/* Single-case switch: `if (msg[2] == 5)` (or `== 5 && ...`) lets mwcc if-convert the
 * inner test into the outer one (ldrbeq/cmpeq); the ROM branches on both. */
extern int  func_ov107_020c08cc(int a, int b, int mode, int c, int d, int e);
extern void func_ov107_020c7500(int a, int b, int c);

void func_ov158_020cebdc(int self, unsigned char *msg, int arg3) {
    switch (msg[2]) {
    case 5:
        if (msg[3] == 0) {
            *(int *)(*(int *)(self + 0x390) + 4) = func_ov107_020c08cc(
                *(int *)(self + 0x3c), *(int *)(*(int *)(self + 0x390)), 5, msg[4], 0x1000,
                (int)(msg + 5));
        }
        break;
    }
    func_ov107_020c7500(self, (int)msg, arg3);
}

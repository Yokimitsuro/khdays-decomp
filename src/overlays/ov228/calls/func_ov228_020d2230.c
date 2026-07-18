/* Single-case switch: `if (msg[2] == 5)` (or `== 5 && ...`) lets mwcc if-convert the
 * inner test into the outer one (ldrbeq/cmpeq); the ROM branches on both. */
extern int  func_ov107_020c09a0(int a, int b, int mode, int anchor, int e, int f);
extern void func_ov107_020c7500(int a, int b, int c);

void func_ov228_020d2230(int self, unsigned char *msg, int arg3) {
    switch (msg[2]) {
    case 5:
        if (msg[3] == 0) {
            *(int *)(self + msg[3] * 8 + 0x394) = func_ov107_020c09a0(
                *(int *)(self + 0x3c), *(int *)(self + msg[3] * 8 + 0x390), 0x17,
                self + 0xa0, msg[4], 0);
        }
        break;
    }
    func_ov107_020c7500(self, (int)msg, arg3);
}

/* func_ov238_020d2adc -- move dispatcher of an ov238 helper: a pending move (+0x1c7 != -1) becomes
 * current (+0x1c6) and its handler (020d2c44 / 020d2d08 / 020d2e30 / 020d30b8 for moves 0-3) is
 * registered in slot 1; the pending slot is always reset to -1. */
extern void func_0203c634(int self, int slot, void (*cb)(void));
extern void func_ov238_020d2c44(void);
extern void func_ov238_020d2d08(void);
extern void func_ov238_020d2e30(void);
extern void func_ov238_020d30b8(void);

void func_ov238_020d2adc(int self) {
    int *ctx;

    ctx = *(int **)(self + 4);
    if (*(signed char *)(ctx[0] + 0x1c7) != -1) {
    *(signed char *)(ctx[0] + 0x1c6) = *(signed char *)(ctx[0] + 0x1c7);
    switch (*(signed char *)(ctx[0] + 0x1c6)) {
    case 0:
        func_0203c634(self, 1, func_ov238_020d2c44);
        break;
    case 1:
        func_0203c634(self, 1, func_ov238_020d2d08);
        break;
    case 2:
        func_0203c634(self, 1, func_ov238_020d2e30);
        break;
    case 3:
        func_0203c634(self, 1, func_ov238_020d30b8);
        break;
    }
    }
    *(signed char *)(ctx[0] + 0x1c7) = -1;
}

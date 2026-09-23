/* func_ov254_020d5048 -- move dispatcher of an ov254 helper: a pending move (+0x1c7 != -1) becomes
 * current (+0x1c6) and its handler (020d5190 / 020d5200 / 020d5278 / 020d52dc for moves 0-3) is
 * registered in slot 1; the pending slot is then reset to -1. */
extern void func_0203c634(int self, int slot, void (*cb)(void));
extern void func_ov254_020d5190(void);
extern void func_ov254_020d5200(void);
extern void func_ov254_020d5278(void);
extern void func_ov254_020d52dc(void);

void func_ov254_020d5048(int self) {
    int *ctx;

    ctx = *(int **)(self + 4);
    if (*(signed char *)(ctx[0] + 0x1c7) == -1) {
        return;
    }
    *(signed char *)(ctx[0] + 0x1c6) = *(signed char *)(ctx[0] + 0x1c7);
    switch (*(signed char *)(ctx[0] + 0x1c6)) {
    case 0:
        func_0203c634(self, 1, func_ov254_020d5190);
        break;
    case 1:
        func_0203c634(self, 1, func_ov254_020d5200);
        break;
    case 2:
        func_0203c634(self, 1, func_ov254_020d5278);
        break;
    case 3:
        func_0203c634(self, 1, func_ov254_020d52dc);
        break;
    }
    *(signed char *)(ctx[0] + 0x1c7) = -1;
}

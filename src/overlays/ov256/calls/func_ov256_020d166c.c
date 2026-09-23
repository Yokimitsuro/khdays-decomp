/* func_ov256_020d166c -- move dispatcher of an ov256 helper: a pending move (+0x1c7 != -1) becomes
 * current (+0x1c6) and its handler (020d1994 / 020d1a40 / 020d1b7c / 020d2054 for moves 0-3) is
 * registered in slot 1; the pending slot is always reset to -1. */
extern void func_0203c634(int self, int slot, void (*cb)(void));
extern void func_ov256_020d1994(void);
extern void func_ov256_020d1a40(void);
extern void func_ov256_020d1b7c(void);
extern void func_ov256_020d2054(void);

void func_ov256_020d166c(int self) {
    int *ctx;

    ctx = *(int **)(self + 4);
    if (*(signed char *)(ctx[0] + 0x1c7) != -1) {
    *(signed char *)(ctx[0] + 0x1c6) = *(signed char *)(ctx[0] + 0x1c7);
    switch (*(signed char *)(ctx[0] + 0x1c6)) {
    case 0:
        func_0203c634(self, 1, func_ov256_020d1994);
        break;
    case 1:
        func_0203c634(self, 1, func_ov256_020d1a40);
        break;
    case 2:
        func_0203c634(self, 1, func_ov256_020d1b7c);
        break;
    case 3:
        func_0203c634(self, 1, func_ov256_020d2054);
        break;
    }
    }
    *(signed char *)(ctx[0] + 0x1c7) = -1;
}

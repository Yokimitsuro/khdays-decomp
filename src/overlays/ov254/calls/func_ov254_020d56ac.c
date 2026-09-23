/* func_ov254_020d56ac -- move dispatcher of an ov254 helper: a pending move (+0x1c7 != -1) becomes
 * current (+0x1c6), bit 0 of the actor's +0x60 high byte is set and bit 7 cleared, and the handler
 * of move 0 / 1 / 2 (020d5790 / 020d5800 / 020d5884) is registered in slot 1; the pending slot is
 * then reset to -1. */
typedef unsigned short u16;
struct Hw60 { u16 lo : 8; u16 hi : 8; };

extern void func_0203c634(int self, int slot, void (*cb)(void));
extern void func_ov254_020d5790(void);
extern void func_ov254_020d5800(void);
extern void func_ov254_020d5884(void);

void func_ov254_020d56ac(int self) {
    int *ctx;

    ctx = *(int **)(self + 4);
    if (*(signed char *)(ctx[0] + 0x1c7) == -1) {
        return;
    }
    *(signed char *)(ctx[0] + 0x1c6) = *(signed char *)(ctx[0] + 0x1c7);
    {
        u16 hw = *(u16 *)(ctx[0] + 0x60);
        *(u16 *)(ctx[0] + 0x60) = (hw & ~0xff00) |
            ((((((unsigned int)hw << 0x10) >> 0x18) | 1) << 0x18) >> 0x10);
    }
    ((struct Hw60 *)(ctx[0] + 0x60))->hi &= ~0x80;
    switch (*(signed char *)(ctx[0] + 0x1c6)) {
    case 0:
        func_0203c634(self, 1, func_ov254_020d5790);
        break;
    case 1:
        func_0203c634(self, 1, func_ov254_020d5800);
        break;
    case 2:
        func_0203c634(self, 1, func_ov254_020d5884);
        break;
    }
    *(signed char *)(ctx[0] + 0x1c7) = -1;
}

/* func_ov254_020d308c -- move dispatcher of an ov254 helper: a pending move (+0x1c7 != -1) becomes
 * current (+0x1c6), bits 1-3 and 7 of the actor's +0x60 high byte clear and bits 0 and 6 are set,
 * the +0x388 shape is armed, +0x1ae bit 0 clears and the handler of moves 0-3 (020d334c / 020d340c
 * / 020d378c / 020d3910) is registered in slot 1; the pending slot is then reset to -1. */
typedef unsigned short u16;
struct Hw60 { u16 lo : 8; u16 hi : 8; };
typedef struct { unsigned f : 8; } B8;

extern void func_0203c634(int self, int slot, void (*cb)(void));
extern void func_ov254_020d334c(void);
extern void func_ov254_020d340c(void);
extern void func_ov254_020d378c(void);
extern void func_ov254_020d3910(void);

void func_ov254_020d308c(int self) {
    int *ctx;

    ctx = *(int **)(self + 4);
    if (*(signed char *)(ctx[0] + 0x1c7) == -1) {
        return;
    }
    *(signed char *)(ctx[0] + 0x1c6) = *(signed char *)(ctx[0] + 0x1c7);
    ((struct Hw60 *)(ctx[0] + 0x60))->hi &= ~0x8e;
    {
        u16 hw = *(u16 *)(ctx[0] + 0x60);
        *(u16 *)(ctx[0] + 0x60) = (hw & ~0xff00) |
            ((((((unsigned int)hw << 0x10) >> 0x18) | 0x41) << 0x18) >> 0x10);
    }
    ((B8 *)(*(int *)(ctx[0] + 0x388) + 8))->f |= 1;
    *(u16 *)(ctx[0] + 0x100 + 0xae) &= ~1;
    switch (*(signed char *)(ctx[0] + 0x1c6)) {
    case 0:
        func_0203c634(self, 1, func_ov254_020d334c);
        break;
    case 1:
        func_0203c634(self, 1, func_ov254_020d340c);
        break;
    case 2:
        func_0203c634(self, 1, func_ov254_020d378c);
        break;
    case 3:
        func_0203c634(self, 1, func_ov254_020d3910);
        break;
    }
    *(signed char *)(ctx[0] + 0x1c7) = -1;
}

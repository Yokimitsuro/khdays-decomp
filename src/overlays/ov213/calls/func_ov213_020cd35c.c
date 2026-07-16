/* func_ov213_020cd35c -- ov213's move dispatcher. The family shape, but with three things of its
 * own:
 *
 *  - the "nothing queued" case RETURNS outright (a predicated `popeq`) instead of falling into the
 *    shared -1 store the way ov210/ov221/ov225/ov228/ov231 do. Written as an early return here;
 *    the `if (x != -1) { ... }` form gives them a branch to the tail instead;
 *  - the timer at +0x48 is refreshed to (*self)[0x2c] * 30 / 10, kept unfolded because that is the
 *    multiply-then-magic-divide the ROM emits;
 *  - +0x1b0 comes from the BYTE at ctx+0x74, not from a halfword.
 *
 * Cases 2 and 5 both dispatch func_ov213_020cdd40 but have their own bodies -- mwcc did not merge
 * them, so they are two separate arms.
 *
 * Form notes: `hi |= 0x40` has no lsl#0x10/lsr#0x10 trunc pair -> explicit extract/reassemble;
 * `hi &= ~0x8e` has one -> bitfield. See codegen-cracks.md. */

typedef struct {
    unsigned short lo : 8;
    unsigned short hi : 8;
} Hw60;

typedef struct {
    unsigned f : 8;
} B8;

extern void func_0203c634(int self, int slot, void (*cb)(void));
extern void func_ov213_020cd654(void);
extern void func_ov213_020cd774(void);
extern void func_ov213_020cda34(void);
extern void func_ov213_020cdd40(void);
extern void func_ov213_020ce080(void);
extern void func_ov213_020ce384(void);
extern void func_ov213_020ce6b0(void);
extern void func_ov213_020cef54(void);
extern void func_ov213_020cf3f0(void);
extern void func_ov213_020cf4ec(void);
extern void func_ov213_020cf684(void);
extern void func_ov213_020cfc90(void);
extern void func_ov213_020cffa4(void);
extern void func_ov213_020d0318(void);
extern void func_ov213_020d03dc(void);

void func_ov213_020cd35c(int self) {
    int *ctx;
    unsigned short v;

    ctx = *(int **)(self + 4);
    if (*(signed char *)(ctx[0] + 0x1c7) == -1) {
        return;
    }

    v = *(unsigned short *)(ctx[0] + 0x60);
    *(unsigned short *)(ctx[0] + 0x60) =
        (unsigned short)((v & ~0xff00)
                         | (((((unsigned int)v << 0x10) >> 0x18 | 0x40) << 0x18) >> 0x10));
    ((Hw60 *)(ctx[0] + 0x60))->hi &= ~0x8e;
    *(unsigned short *)(ctx[0] + 0x1ae) &= ~1;
    ((B8 *)(*(int *)(ctx[0] + 0x3d4) + 8))->f |= 1;

    ctx[0x12] = *(int *)(*(int *)self + 0x2c) * 30 / 10;
    *(unsigned short *)(ctx[0] + 0x1b0) = *(unsigned char *)((char *)ctx + 0x74);
    *(signed char *)(ctx[0] + 0x1c6) = *(signed char *)(ctx[0] + 0x1c7);

    switch (*(signed char *)(ctx[0] + 0x1c6)) {
    case 0:
        func_0203c634(self, 1, func_ov213_020cd654);
        break;
    case 1:
        func_0203c634(self, 1, func_ov213_020cd774);
        break;
    /* Case 2 re-queues itself as move 5 and FALLS THROUGH into it -- the ROM's case-5 table entry
     * points 8 bytes into case 2's body, past the store. (The store is dead in the original: the
     * tail overwrites +0x1c7 with -1 regardless. Reproduced because the ROM has it.) */
    case 2:
        *(signed char *)(ctx[0] + 0x1c7) = 5;
        /* fall through */
    case 5:
        func_0203c634(self, 1, func_ov213_020cdd40);
        break;
    case 4:
        func_0203c634(self, 1, func_ov213_020cda34);
        break;
    case 6:
        func_0203c634(self, 1, func_ov213_020ce080);
        break;
    case 7:
        func_0203c634(self, 1, func_ov213_020ce384);
        break;
    case 8:
        func_0203c634(self, 1, func_ov213_020ce6b0);
        break;
    case 9:
        func_0203c634(self, 1, func_ov213_020cef54);
        break;
    case 10:
        func_0203c634(self, 1, func_ov213_020cf3f0);
        break;
    case 11:
        func_0203c634(self, 1, func_ov213_020cf4ec);
        break;
    case 12:
        func_0203c634(self, 1, func_ov213_020cf684);
        break;
    case 13:
        func_0203c634(self, 1, func_ov213_020cfc90);
        break;
    case 14:
        func_0203c634(self, 1, func_ov213_020cffa4);
        break;
    case 3:
        func_0203c634(self, 1, func_ov213_020d0318);
        break;
    case 15:
        func_0203c634(self, 1, func_ov213_020d03dc);
        break;
    }

    *(signed char *)(ctx[0] + 0x1c7) = -1;
}

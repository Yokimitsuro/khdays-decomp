/* func_ov222_020d32f4 -- ov221's move dispatcher. Same shape as the ov210/ov228/ov231 ones: -1 at
 * ctx[0]+0x1c7 means nothing queued, the id is copied to +0x1c6 and it is that copy the switch
 * reads, and the slot is cleared on every path.
 *
 * The reset here is the richest of the family. Besides clearing 0xc6 from the hw60 hi-byte and
 * bits 0-1 of the halfword at +0x1ae, it toggles bit 0 on four sub-objects (+0x3b0 cleared,
 * +0x3b4/+0x3b8/+0x3bc set), and the flag at ctx+0x78 gates two of them: it adds 0x40 to the
 * hw60 and flips the sense of the +0x3ac bit. So +0x78 is "the alternate stance is up".
 *
 * Case 7 is absent from the switch -- its jump-table slot points at the default, which is how mwcc
 * fills a gap in an otherwise dense table. The source case order is the body order (13 and 16 sit
 * out of place, and 3 is late as in every other dispatcher).
 *
 * Form notes (codegen-cracks.md): `hi &= ~0xc6` HAS the lsl#0x10/lsr#0x10 trunc pair so it takes
 * the bitfield form, while `hi |= 0x40` does NOT and needs the explicit extract/reassemble; the
 * +8 fields are byte-in-word. */

typedef struct {
    unsigned short lo : 8;
    unsigned short hi : 8;
} Hw60;

typedef struct {
    unsigned f : 8;
} B8;

extern void func_0203c634(int self, int slot, void (*cb)(void));
extern void func_ov222_020d39a0(void);
extern void func_ov222_020d3a6c(void);
extern void func_ov222_020d3c5c(void);
extern void func_ov222_020d3dd8(void);
extern void func_ov222_020d3d88(void);
extern void func_ov222_020d411c(void);
extern void func_ov222_020d4358(void);
extern void func_ov222_020d46a8(void);
extern void func_ov222_020d4ac8(void);
extern void func_ov222_020d50a0(void);
extern void func_ov222_020d52ec(void);
extern void func_ov222_020d5768(void);
extern void func_ov222_020d58b8(void);
extern void func_ov222_020d59b0(void);
extern void func_ov222_020d5aa8(void);
extern void func_ov222_020d5c14(void);

void func_ov222_020d32f4(int self) {
    int *ctx;
    unsigned short v;

    ctx = *(int **)(self + 4);
    if (*(signed char *)(ctx[0] + 0x1c7) != -1) {
        *(signed char *)(ctx[0] + 0x1c6) = *(signed char *)(ctx[0] + 0x1c7);
        ((Hw60 *)(ctx[0] + 0x60))->hi &= ~0xc6;
        *(unsigned short *)(ctx[0] + 0x1ae) &= ~3;

        if (ctx[0x1e] != 0) {
            v = *(unsigned short *)(ctx[0] + 0x60);
            *(unsigned short *)(ctx[0] + 0x60) =
                (unsigned short)((v & ~0xff00)
                                 | (((((unsigned int)v << 0x10) >> 0x18 | 0x40) << 0x18) >> 0x10));
        }

        ((B8 *)(*(int *)(ctx[0] + 0x3b0) + 8))->f &= ~1;
        ((B8 *)(*(int *)(ctx[0] + 0x3b4) + 8))->f |= 1;
        ((B8 *)(*(int *)(ctx[0] + 0x3b8) + 8))->f |= 1;
        ((B8 *)(*(int *)(ctx[0] + 0x3bc) + 8))->f |= 1;

        if (ctx[0x1e] != 0) {
            ((B8 *)(*(int *)(ctx[0] + 0x3ac) + 8))->f &= ~1;
        } else {
            ((B8 *)(*(int *)(ctx[0] + 0x3ac) + 8))->f |= 1;
        }

        switch (*(signed char *)(ctx[0] + 0x1c6)) {
        case 0:
            func_0203c634(self, 1, func_ov222_020d39a0);
            break;
        case 1:
            func_0203c634(self, 1, func_ov222_020d3a6c);
            break;
        case 4:
            func_0203c634(self, 1, func_ov222_020d3c5c);
            break;
        case 5:
            func_0203c634(self, 1, func_ov222_020d3dd8);
            break;
        case 13:
            func_0203c634(self, 1, func_ov222_020d3d88);
            break;
        case 2:
            func_0203c634(self, 1, func_ov222_020d411c);
            break;
        case 6:
            func_0203c634(self, 1, func_ov222_020d4358);
            break;
        case 9:
            func_0203c634(self, 1, func_ov222_020d4ac8);
            break;
        case 10:
            func_0203c634(self, 1, func_ov222_020d50a0);
            break;
        case 11:
            func_0203c634(self, 1, func_ov222_020d52ec);
            break;
        case 16:
            func_0203c634(self, 1, func_ov222_020d5768);
            break;
        case 8:
            func_0203c634(self, 1, func_ov222_020d46a8);
            break;
        case 12:
            func_0203c634(self, 1, func_ov222_020d58b8);
            break;
        case 3:
            func_0203c634(self, 1, func_ov222_020d59b0);
            break;
        case 14:
            func_0203c634(self, 1, func_ov222_020d5aa8);
            break;
        case 15:
            func_0203c634(self, 1, func_ov222_020d5c14);
            break;
        }
    }

    *(signed char *)(ctx[0] + 0x1c7) = -1;
}

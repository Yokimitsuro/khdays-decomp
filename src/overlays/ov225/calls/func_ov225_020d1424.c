/* func_ov225_020d1424 -- ov225's move dispatcher. Same family shape as func_ov221_020d14d4 (test
 * ctx[0]+0x1c7 against -1, reset, copy the id to +0x1c6, dense jump table of c634 entries, clear
 * the slot); it differs only in the reset and in having a case 7, which ov221 lacks.
 *
 * The flag at ctx+0x78 -- "the alternate stance is up" -- still gates the extra 0x40 on the hw60.
 *
 * ★ Bit 0 of the sub-object at ctx[0]+0x3b0 is CLEARED near the top and SET again at the bottom.
 * That is redundant and it is what the ROM does; ov221 clears it and leaves it. Do not tidy it
 * away -- the second write is a real instruction sequence in the original.
 *
 * Form notes (codegen-cracks.md): `hi &= ~0xc6` has the lsl#0x10/lsr#0x10 trunc pair so it takes
 * the bitfield form, while `hi |= 0x40` does not and needs the explicit extract/reassemble; the
 * +8 fields are byte-in-word. */

typedef struct {
    unsigned short lo : 8;
    unsigned short hi : 8;
} Hw60;

typedef struct {
    unsigned f : 8;
} B8;

extern void func_0203c634(int self, int slot, void (*cb)(void));
extern void func_ov225_020d1aec(void);
extern void func_ov225_020d1bb8(void);
extern void func_ov225_020d1da8(void);
extern void func_ov225_020d1f24(void);
extern void func_ov225_020d1ed4(void);
extern void func_ov225_020d2268(void);
extern void func_ov225_020d24ac(void);
extern void func_ov225_020d27fc(void);
extern void func_ov225_020d2b74(void);
extern void func_ov225_020d2f98(void);
extern void func_ov225_020d3570(void);
extern void func_ov225_020d37bc(void);
extern void func_ov225_020d3c38(void);
extern void func_ov225_020d3d84(void);
extern void func_ov225_020d3e7c(void);
extern void func_ov225_020d3f74(void);
extern void func_ov225_020d40e0(void);

void func_ov225_020d1424(int self) {
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
        ((B8 *)(*(int *)(ctx[0] + 0x3ac) + 8))->f |= 1;
        ((B8 *)(*(int *)(ctx[0] + 0x3b0) + 8))->f |= 1;

        switch (*(signed char *)(ctx[0] + 0x1c6)) {
        case 0:
            func_0203c634(self, 1, func_ov225_020d1aec);
            break;
        case 1:
            func_0203c634(self, 1, func_ov225_020d1bb8);
            break;
        case 4:
            func_0203c634(self, 1, func_ov225_020d1da8);
            break;
        case 5:
            func_0203c634(self, 1, func_ov225_020d1f24);
            break;
        case 13:
            func_0203c634(self, 1, func_ov225_020d1ed4);
            break;
        case 2:
            func_0203c634(self, 1, func_ov225_020d2268);
            break;
        case 6:
            func_0203c634(self, 1, func_ov225_020d24ac);
            break;
        case 7:
            func_0203c634(self, 1, func_ov225_020d27fc);
            break;
        case 9:
            func_0203c634(self, 1, func_ov225_020d2f98);
            break;
        case 10:
            func_0203c634(self, 1, func_ov225_020d3570);
            break;
        case 11:
            func_0203c634(self, 1, func_ov225_020d37bc);
            break;
        case 16:
            func_0203c634(self, 1, func_ov225_020d3c38);
            break;
        case 8:
            func_0203c634(self, 1, func_ov225_020d2b74);
            break;
        case 12:
            func_0203c634(self, 1, func_ov225_020d3d84);
            break;
        case 3:
            func_0203c634(self, 1, func_ov225_020d3e7c);
            break;
        case 14:
            func_0203c634(self, 1, func_ov225_020d3f74);
            break;
        case 15:
            func_0203c634(self, 1, func_ov225_020d40e0);
            break;
        }
    }

    *(signed char *)(ctx[0] + 0x1c7) = -1;
}

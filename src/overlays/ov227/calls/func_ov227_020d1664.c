/* func_ov227_020d1664 -- ov227's move dispatcher. The ov221/ov225 shape, and the three of them
 * differ only in the tail of the reset:
 *   ov221 -- the +0x3ac bit is CONDITIONAL on ctx+0x78 (set when the flag is clear, cleared when
 *            it is set);
 *   ov225 -- +0x3ac is set unconditionally, and +0x3b0 is then set again after being cleared;
 *   ov227 -- +0x3ac is set unconditionally and that is the end of it (this one).
 * Case 7 is absent from the switch, as in ov221; ov225 has it.
 *
 * ctx+0x78 -- the alternate stance -- still gates the extra 0x40 on the hw60.
 *
 * Form notes (codegen-cracks.md): `hi &= ~0xc6` has the lsl#0x10/lsr#0x10 trunc pair so it takes
 * the bitfield form, `hi |= 0x40` does not and needs the explicit extract/reassemble, and the +8
 * fields are byte-in-word. */

typedef struct {
    unsigned short lo : 8;
    unsigned short hi : 8;
} Hw60;

typedef struct {
    unsigned f : 8;
} B8;

extern void func_0203c634(int self, int slot, void (*cb)(void));
extern void func_ov227_020d1da0(void);
extern void func_ov227_020d1e68(void);
extern void func_ov227_020d2058(void);
extern void func_ov227_020d21d4(void);
extern void func_ov227_020d2184(void);
extern void func_ov227_020d24e0(void);
extern void func_ov227_020d2724(void);
extern void func_ov227_020d2928(void);
extern void func_ov227_020d2b14(void);
extern void func_ov227_020d30ec(void);
extern void func_ov227_020d3338(void);
extern void func_ov227_020d37b4(void);
extern void func_ov227_020d3900(void);
extern void func_ov227_020d39f8(void);
extern void func_ov227_020d3af0(void);
extern void func_ov227_020d3c5c(void);

void func_ov227_020d1664(int self) {
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

        switch (*(signed char *)(ctx[0] + 0x1c6)) {
        case 0:
            func_0203c634(self, 1, func_ov227_020d1da0);
            break;
        case 1:
            func_0203c634(self, 1, func_ov227_020d1e68);
            break;
        case 4:
            func_0203c634(self, 1, func_ov227_020d2058);
            break;
        case 5:
            func_0203c634(self, 1, func_ov227_020d21d4);
            break;
        case 13:
            func_0203c634(self, 1, func_ov227_020d2184);
            break;
        case 2:
            func_0203c634(self, 1, func_ov227_020d24e0);
            break;
        case 6:
            func_0203c634(self, 1, func_ov227_020d2724);
            break;
        case 9:
            func_0203c634(self, 1, func_ov227_020d2b14);
            break;
        case 10:
            func_0203c634(self, 1, func_ov227_020d30ec);
            break;
        case 11:
            func_0203c634(self, 1, func_ov227_020d3338);
            break;
        case 16:
            func_0203c634(self, 1, func_ov227_020d37b4);
            break;
        case 8:
            func_0203c634(self, 1, func_ov227_020d2928);
            break;
        case 12:
            func_0203c634(self, 1, func_ov227_020d3900);
            break;
        case 3:
            func_0203c634(self, 1, func_ov227_020d39f8);
            break;
        case 14:
            func_0203c634(self, 1, func_ov227_020d3af0);
            break;
        case 15:
            func_0203c634(self, 1, func_ov227_020d3c5c);
            break;
        }
    }

    *(signed char *)(ctx[0] + 0x1c7) = -1;
}

/* func_ov272_020d0b00 -- ov272's move dispatcher.
 *
 * Byte-identical reset and case order to func_ov119_020ccef4; only the handlers differ.
 * Same shape as func_ov146_020cc8f0: the reset ORs 0x40 into the hw60 hi-byte and then clears 0x8e
 * from it, and only drops bit 0 of the halfword at +0x1ae. Unlike ov146 the id is copied to +0x1c6
 * LATE, after the flag work.
 *
 * Case 3 is out of order (after 4) as everywhere else.
 *
 * Form notes (codegen-cracks.md): `hi |= 0x40` has no lsl#0x10/lsr#0x10 trunc pair so it needs the
 * explicit extract/reassemble, while `hi &= ~0x8e` has one and takes the bitfield form -- the same
 * two opposite forms back to back as in ov146. */

typedef struct {
    unsigned short lo : 8;
    unsigned short hi : 8;
} Hw60;

typedef struct {
    unsigned f : 8;
} B8;

extern void func_0203c634(int self, int slot, void (*cb)(void));
extern void func_ov272_020d0d50(void);
extern void func_ov272_020d0e38(void);
extern void func_ov272_020d1034(void);
extern void func_ov272_020d1408(void);
extern void func_ov272_020d159c(void);
extern void func_ov272_020d108c(void);
extern void func_ov272_020d1664(void);
extern void func_ov272_020d16cc(void);
extern void func_ov272_020d1a74(void);
extern void func_ov272_020d215c(void);
extern void func_ov272_020d2614(void);
extern void func_ov272_020d3328(void);

void func_ov272_020d0b00(int self) {
    int *ctx;
    unsigned short v;

    ctx = *(int **)(self + 4);
    if (*(signed char *)(ctx[0] + 0x1c7) != -1) {
        v = *(unsigned short *)(ctx[0] + 0x60);
        *(unsigned short *)(ctx[0] + 0x60) =
            (unsigned short)((v & ~0xff00)
                             | (((((unsigned int)v << 0x10) >> 0x18 | 0x40) << 0x18) >> 0x10));
        ((Hw60 *)(ctx[0] + 0x60))->hi &= ~0x8e;
        *(unsigned short *)(ctx[0] + 0x1ae) &= ~1;
        ((B8 *)(*(int *)(ctx[0] + 0x388) + 8))->f |= 1;
        *(signed char *)(ctx[0] + 0x1c6) = *(signed char *)(ctx[0] + 0x1c7);

        switch (*(signed char *)(ctx[0] + 0x1c6)) {
        case 0:
            func_0203c634(self, 1, func_ov272_020d0d50);
            break;
        case 1:
            func_0203c634(self, 1, func_ov272_020d0e38);
            break;
        case 2:
            func_0203c634(self, 1, func_ov272_020d1034);
            break;
        case 4:
            func_0203c634(self, 1, func_ov272_020d1408);
            break;
        case 3:
            func_0203c634(self, 1, func_ov272_020d159c);
            break;
        case 5:
            func_0203c634(self, 1, func_ov272_020d108c);
            break;
        case 6:
            func_0203c634(self, 1, func_ov272_020d1664);
            break;
        case 7:
            func_0203c634(self, 1, func_ov272_020d16cc);
            break;
        case 8:
            func_0203c634(self, 1, func_ov272_020d1a74);
            break;
        case 9:
            func_0203c634(self, 1, func_ov272_020d215c);
            break;
        case 10:
            func_0203c634(self, 1, func_ov272_020d2614);
            break;
        case 11:
            func_0203c634(self, 1, func_ov272_020d3328);
            break;
        }
    }

    *(signed char *)(ctx[0] + 0x1c7) = -1;
}

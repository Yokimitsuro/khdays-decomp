/* func_ov232_020d0ef4 -- ov231's move dispatcher, the counterpart of func_ov228_020cf47c: play
 * whatever move is queued at ctx[0]+0x1c7 and clear the slot. -1 means nothing queued and the
 * whole body is skipped, but the slot is cleared either way.
 *
 * Before dispatching it resets the move state: bit 0 of the halfword at +0x1ae, the probe bitmask
 * at ctx+0x4d, bit 0 SET and bit 1 CLEARED on the target's byte field at +8, and the hw60 flags.
 * The id is then copied to +0x1c6, and it is that copy the switch reads.
 *
 * The 15 handlers are the ov231 state family -- func_ov232_020d0e54 (the tick),
 * func_ov232_020d16e8 (the sidestep chooser), and so on. Case 12 is absent from the switch; its
 * jump-table entry points at the default, which is how mwcc fills a gap in an otherwise dense
 * table.
 *
 * Source case order is 0,1,2,4,11,5,6,7,8,9,10,3,13,14 -- that is the order the ROM lays the
 * bodies out, and with a jump table the body order IS the source order (the table itself is
 * index-ordered). Do not tidy it.
 *
 * ★ Both hw60 forms appear here back to back, and they need OPPOSITE C (see codegen-cracks.md):
 * `hi |= 0x40` has no `lsl#0x10 ; lsr#0x10` trunc pair -> explicit extract/reassemble with
 * `v & ~0xff00` for the lo-byte keep; `hi &= ~0x9e` has the pair -> bitfield form. */

typedef struct {
    unsigned short lo : 8;
    unsigned short hi : 8;
} Hw60;

typedef struct {
    unsigned f : 8;
} B8;

extern void func_0203c634(int self, int slot, void (*cb)(void));
extern void func_ov232_020d0e54(void);
extern void func_ov232_020d13a8(void);
extern void func_ov232_020d153c(void);
extern void func_ov232_020d16e8(void);
extern void func_ov232_020d1c3c(void);
extern void func_ov232_020d1e14(void);
extern void func_ov232_020d20ac(void);
extern void func_ov232_020d2358(void);
extern void func_ov232_020d25dc(void);
extern void func_ov232_020d28dc(void);
extern void func_ov232_020d29e0(void);
extern void func_ov232_020d2b10(void);
extern void func_ov232_020d2bd8(void);
extern void func_ov232_020d2ae0(void);

void func_ov232_020d0ef4(int self) {
    int *ctx;
    unsigned short v;

    ctx = *(int **)(self + 4);
    if (*(signed char *)(ctx[0] + 0x1c7) != -1) {
        *(unsigned short *)(ctx[0] + 0x1ae) &= ~1;
        *(unsigned char *)((char *)ctx + 0x4d) = 0;
        ((B8 *)(*(int *)(ctx[0] + 0x3bc) + 8))->f |= 1;
        ((B8 *)(*(int *)(ctx[0] + 0x3bc) + 8))->f &= ~2;

        v = *(unsigned short *)(ctx[0] + 0x60);
        *(unsigned short *)(ctx[0] + 0x60) =
            (unsigned short)((v & ~0xff00)
                             | (((((unsigned int)v << 0x10) >> 0x18 | 0x40) << 0x18) >> 0x10));
        ((Hw60 *)(ctx[0] + 0x60))->hi &= ~0x9e;

        *(signed char *)(ctx[0] + 0x1c6) = *(signed char *)(ctx[0] + 0x1c7);

        switch (*(signed char *)(ctx[0] + 0x1c6)) {
        case 0:
            func_0203c634(self, 1, func_ov232_020d0e54);
            break;
        case 1:
            func_0203c634(self, 1, func_ov232_020d13a8);
            break;
        case 2:
            func_0203c634(self, 1, func_ov232_020d153c);
            break;
        case 4:
            func_0203c634(self, 1, func_ov232_020d16e8);
            break;
        case 11:
            func_0203c634(self, 1, func_ov232_020d1c3c);
            break;
        case 5:
            func_0203c634(self, 1, func_ov232_020d1e14);
            break;
        case 6:
            func_0203c634(self, 1, func_ov232_020d20ac);
            break;
        case 7:
            func_0203c634(self, 1, func_ov232_020d2358);
            break;
        case 8:
            func_0203c634(self, 1, func_ov232_020d25dc);
            break;
        case 9:
            func_0203c634(self, 1, func_ov232_020d28dc);
            break;
        case 10:
            func_0203c634(self, 1, func_ov232_020d29e0);
            break;
        case 3:
            func_0203c634(self, 1, func_ov232_020d2b10);
            break;
        case 13:
            func_0203c634(self, 1, func_ov232_020d2bd8);
            break;
        case 14:
            func_0203c634(self, 1, func_ov232_020d2ae0);
            break;
        }
    }

    *(signed char *)(ctx[0] + 0x1c7) = -1;
}

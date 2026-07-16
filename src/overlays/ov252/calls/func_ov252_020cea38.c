/* func_ov252_020cea38 -- ov252's move dispatcher.
 *
 * Two small departures from the family: the hw60 gets 0x14 ADDED before 0x8a is cleared (most of
 * the others only clear), and the id is copied from +0x1c7 to +0x1c6 AFTER the flag work rather
 * than before it. Neither changes what the switch reads, but both are visible in the order.
 *
 * Cases 1 and 9 are absent from the switch; case 3 is out of order (after 11) as everywhere else.
 *
 * Form notes (codegen-cracks.md): `hi |= 0x14` has no lsl#0x10/lsr#0x10 trunc pair so it needs the
 * explicit extract/reassemble, while `hi &= ~0x8a` has one and takes the bitfield form. Two
 * opposite forms, back to back, in one function -- as in func_ov231_020cf578. */

typedef struct {
    unsigned short lo : 8;
    unsigned short hi : 8;
} Hw60;

extern void func_0203c634(int self, int slot, void (*cb)(void));
extern void func_ov252_020cf0c4(void);
extern void func_ov252_020cf218(void);
extern void func_ov252_020cf3b8(void);
extern void func_ov252_020cfce0(void);
extern void func_ov252_020d02f8(void);
extern void func_ov252_020d03b0(void);
extern void func_ov252_020d08e8(void);
extern void func_ov252_020d14cc(void);
extern void func_ov252_020d184c(void);
extern void func_ov252_020d19fc(void);
extern void func_ov252_020d27a8(void);
extern void func_ov252_020d2c84(void);
extern void func_ov252_020d2d00(void);

void func_ov252_020cea38(int self) {
    int *ctx;
    unsigned short v;

    ctx = *(int **)(self + 4);
    if (*(signed char *)(ctx[0] + 0x1c7) != -1) {
        v = *(unsigned short *)(ctx[0] + 0x60);
        *(unsigned short *)(ctx[0] + 0x60) =
            (unsigned short)((v & ~0xff00)
                             | (((((unsigned int)v << 0x10) >> 0x18 | 0x14) << 0x18) >> 0x10));
        ((Hw60 *)(ctx[0] + 0x60))->hi &= ~0x8a;
        *(unsigned short *)(ctx[0] + 0x1ae) &= ~3;
        *(signed char *)(ctx[0] + 0x1c6) = *(signed char *)(ctx[0] + 0x1c7);

        switch (*(signed char *)(ctx[0] + 0x1c6)) {
        case 0:
            func_0203c634(self, 1, func_ov252_020cf0c4);
            break;
        case 2:
            func_0203c634(self, 1, func_ov252_020cf218);
            break;
        case 4:
            func_0203c634(self, 1, func_ov252_020cf3b8);
            break;
        case 5:
            func_0203c634(self, 1, func_ov252_020cfce0);
            break;
        case 6:
            func_0203c634(self, 1, func_ov252_020d03b0);
            break;
        case 7:
            func_0203c634(self, 1, func_ov252_020d08e8);
            break;
        case 8:
            func_0203c634(self, 1, func_ov252_020d14cc);
            break;
        case 10:
            func_0203c634(self, 1, func_ov252_020d27a8);
            break;
        case 11:
            func_0203c634(self, 1, func_ov252_020d184c);
            break;
        case 3:
            func_0203c634(self, 1, func_ov252_020d2d00);
            break;
        case 12:
            func_0203c634(self, 1, func_ov252_020d2c84);
            break;
        case 13:
            func_0203c634(self, 1, func_ov252_020d19fc);
            break;
        case 14:
            func_0203c634(self, 1, func_ov252_020d02f8);
            break;
        }
    }

    *(signed char *)(ctx[0] + 0x1c7) = -1;
}

/*
 * Message handler: 0x21 turns the actor to face its stored heading, 0x22 reports one of two
 * codes depending on the block's state, 0x23 just hands over.
 *
 * A global gate at data_0204c240 bit 2 can FORCE the message to 0x21: when that bit is clear
 * and the 64-bit field at self+0 has bit 8 set, the incoming message is overridden.
 *
 * THREE LEVERS, all already in the catalogue and all needed together:
 *  - the bit test is a 64-BIT AND.  `*(long long *)self & 0x100` is what produces the ROM's
 *    `and r3, r3, #0x100` on the low half, `and r2, r2, r0` with zero on the high half, and
 *    the `cmp` / `cmpeq` pair.  Same family as the 64-bit OR that unblocked three other
 *    families today -- when a mask is applied to one word and ZERO to the next one up, that
 *    is one 64-bit field, not two operations.
 *  - `next = 0` is initialised BEFORE the gate, so its zero doubles as the comparison
 *    operand for the 64-bit test.  The ROM's single `mov r0, #0` serves both.
 *  - the dispatch is a SWITCH.  The ROM emits all three comparisons and the shared epilogue
 *    first and places the case bodies after; an if-chain falls into the first body inline.
 *    The 0x23 arm is predicated into that shared epilogue (`ldreq r0, [pc]`), which is what
 *    the `next` variable plus `break` gives.
 */
typedef struct { int x, y, z; } Vec3;

extern int VEC_Mag(const Vec3 *v);
extern int func_01ff8d18(const Vec3 *v, Vec3 *unit);
extern int FX_Atan2(int x, int z);
extern unsigned char data_0204c240;
extern void func_ov104_020bbd80(void);
extern void func_ov104_020baf48(void);
extern void func_ov104_020bbba0(void);

void *func_ov104_020bab90(char *self, int msg) {
    char *blk = self + 0xfc + 0x2c00;
    void *next = 0;
    Vec3 d;
    unsigned short a;
    int *node;

    if ((data_0204c240 & 4) == 0) {
        if ((*(long long *)self & 0x100) != 0) {
            msg = 0x21;
        }
    }

    switch (msg) {
    case 0x21:
        (*(void (**)(char *, int))(self + 0x664))(self, 0x1b);
        *(int *)(self + 0x58) = 0;
        d = *(Vec3 *)(self + 0x7c + 0x400);
        d.y = 0;
        if (VEC_Mag(&d) != 0) {
            func_01ff8d18(&d, &d);
        }
        a = (unsigned short)FX_Atan2(d.x, d.z);
        node = *(int **)(self + 0x20);
        if ((node[0] & 0x20) == 0) {
            *(unsigned short *)((char *)node + 0x80) = a + 0x8000;
            *(unsigned short *)((char *)node + 4) |= 0x20;
        }
        return (void *)&func_ov104_020baf48;
    case 0x22:
        if (*(int *)(blk + 0x118) != 0) {
            (*(void (**)(char *, int))(self + 0x664))(self, 0x30);
        } else {
            (*(void (**)(char *, int))(self + 0x664))(self, 0x2f);
        }
        return (void *)&func_ov104_020bbba0;
    case 0x23:
        next = (void *)&func_ov104_020bbd80;
        break;
    }
    return next;
}

/* func_ov146_020cc8f0 -- ov146's move dispatcher.
 *
 * Its reset ADDS 0x40 to the hw60 hi-byte before clearing 0x86 from it, and only drops bit 1 of
 * the halfword at +0x1ae (most of the family clears bits 0-1). Then bit 0 goes on the sub-object
 * at ctx[0]+0x3ac.
 *
 * Case 3 is out of order (after 9) as everywhere else.
 *
 * Form notes (codegen-cracks.md): `hi |= 0x40` has no lsl#0x10/lsr#0x10 trunc pair so it needs the
 * explicit extract/reassemble, while `hi &= ~0x86` has one and takes the bitfield form -- two
 * opposite forms back to back, as in func_ov231_020cf578 and func_ov252_020cea38. */

typedef struct {
    unsigned short lo : 8;
    unsigned short hi : 8;
} Hw60;

typedef struct {
    unsigned f : 8;
} B8;

extern void func_0203c634(int self, int slot, void (*cb)(void));
extern void func_ov146_020ccd78(void);
extern void func_ov146_020cce4c(void);
extern void func_ov146_020cd0d8(void);
extern void func_ov146_020cd174(void);
extern void func_ov146_020cd700(void);
extern void func_ov146_020cd7f0(void);
extern void func_ov146_020cd91c(void);
extern void func_ov146_020cdb78(void);
extern void func_ov146_020cdcb4(void);
extern void func_ov146_020cdeb8(void);
extern void func_ov146_020cdfdc(void);
extern void func_ov146_020ce170(void);

void func_ov146_020cc8f0(int self) {
    int *ctx;
    unsigned short v;

    ctx = *(int **)(self + 4);
    if (*(signed char *)(ctx[0] + 0x1c7) != -1) {
        *(signed char *)(ctx[0] + 0x1c6) = *(signed char *)(ctx[0] + 0x1c7);

        v = *(unsigned short *)(ctx[0] + 0x60);
        *(unsigned short *)(ctx[0] + 0x60) =
            (unsigned short)((v & ~0xff00)
                             | (((((unsigned int)v << 0x10) >> 0x18 | 0x40) << 0x18) >> 0x10));
        ((Hw60 *)(ctx[0] + 0x60))->hi &= ~0x86;
        *(unsigned short *)(ctx[0] + 0x1ae) &= ~2;
        ((B8 *)(*(int *)(ctx[0] + 0x3ac) + 8))->f |= 1;

        switch (*(signed char *)(ctx[0] + 0x1c6)) {
        case 0:
            func_0203c634(self, 1, func_ov146_020ccd78);
            break;
        case 1:
            func_0203c634(self, 1, func_ov146_020cce4c);
            break;
        case 2:
            func_0203c634(self, 1, func_ov146_020cd0d8);
            break;
        case 4:
            func_0203c634(self, 1, func_ov146_020cd174);
            break;
        case 5:
            func_0203c634(self, 1, func_ov146_020cd700);
            break;
        case 6:
            func_0203c634(self, 1, func_ov146_020cd7f0);
            break;
        case 7:
            func_0203c634(self, 1, func_ov146_020cd91c);
            break;
        case 8:
            func_0203c634(self, 1, func_ov146_020cdb78);
            break;
        case 9:
            func_0203c634(self, 1, func_ov146_020cdcb4);
            break;
        case 3:
            func_0203c634(self, 1, func_ov146_020cdeb8);
            break;
        case 10:
            func_0203c634(self, 1, func_ov146_020cdfdc);
            break;
        case 11:
            func_0203c634(self, 1, func_ov146_020ce170);
            break;
        }
    }

    *(signed char *)(ctx[0] + 0x1c7) = -1;
}

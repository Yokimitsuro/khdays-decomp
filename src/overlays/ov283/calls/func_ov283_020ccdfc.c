/* func_ov283_020ccdfc -- ov283's move dispatcher. The plain family shape: -1 at ctx[0]+0x1c7 means
 * nothing queued, the id is copied to +0x1c6 and it is that copy the switch reads, and the slot is
 * cleared on every path.
 *
 * The reset drops 0xc6 from the hw60 hi-byte and bits 0-1 of the halfword at +0x1ae, then sets bit
 * 0 on the sub-object at ctx[0]+0x388.
 *
 * Case 1 is absent from the switch. The source case order (0,2,4,5,6,10,8,9,7,11,3) is the body
 * order -- 10 and 7 are out of place as well as the usual 3.
 *
 * The hw60 write HAS the lsl#0x10/lsr#0x10 trunc pair -> bitfield form; the +8 field is
 * byte-in-word. See codegen-cracks.md. */

typedef struct {
    unsigned short lo : 8;
    unsigned short hi : 8;
} Hw60;

typedef struct {
    unsigned f : 8;
} B8;

extern void func_0203c634(int self, int slot, void (*cb)(void));
extern void func_ov283_020cd108(void);
extern void func_ov283_020cd200(void);
extern void func_ov283_020cd558(void);
extern void func_ov283_020cd8f8(void);
extern void func_ov283_020cdb88(void);
extern void func_ov283_020cddec(void);
extern void func_ov283_020ce0bc(void);
extern void func_ov283_020ce328(void);
extern void func_ov283_020ce6e0(void);
extern void func_ov283_020cea7c(void);
extern void func_ov283_020ced2c(void);

void func_ov283_020ccdfc(int self) {
    int *ctx;

    ctx = *(int **)(self + 4);
    if (*(signed char *)(ctx[0] + 0x1c7) != -1) {
        *(signed char *)(ctx[0] + 0x1c6) = *(signed char *)(ctx[0] + 0x1c7);
        ((Hw60 *)(ctx[0] + 0x60))->hi &= ~0xc6;
        *(unsigned short *)(ctx[0] + 0x1ae) &= ~3;
        ((B8 *)(*(int *)(ctx[0] + 0x388) + 8))->f |= 1;

        switch (*(signed char *)(ctx[0] + 0x1c6)) {
        case 0:
            func_0203c634(self, 1, func_ov283_020cd108);
            break;
        case 2:
            func_0203c634(self, 1, func_ov283_020cd200);
            break;
        case 4:
            func_0203c634(self, 1, func_ov283_020cd558);
            break;
        case 5:
            func_0203c634(self, 1, func_ov283_020cd8f8);
            break;
        case 6:
            func_0203c634(self, 1, func_ov283_020cdb88);
            break;
        case 10:
            func_0203c634(self, 1, func_ov283_020cddec);
            break;
        case 8:
            func_0203c634(self, 1, func_ov283_020ce0bc);
            break;
        case 9:
            func_0203c634(self, 1, func_ov283_020ce328);
            break;
        case 7:
            func_0203c634(self, 1, func_ov283_020ce6e0);
            break;
        case 11:
            func_0203c634(self, 1, func_ov283_020cea7c);
            break;
        case 3:
            func_0203c634(self, 1, func_ov283_020ced2c);
            break;
        }
    }

    *(signed char *)(ctx[0] + 0x1c7) = -1;
}

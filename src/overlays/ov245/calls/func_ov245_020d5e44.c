/* func_ov245_020d5e44 -- ov238's move dispatcher. The plain family shape: -1 at ctx[0]+0x1c7 means
 * nothing queued, the id is copied to +0x1c6 and it is that copy the switch reads, and the slot is
 * cleared on every path.
 *
 * The reset drops 0xce from the hw60 hi-byte and bit 0 of the halfword at +0x1ae, then sets bit
 * 0 on the sub-object at ctx[0]+0x388.
 *
 * Case 3 is out of order (after 8) as everywhere else.
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
extern void func_ov245_020d607c(void);
extern void func_ov245_020d60e0(void);
extern void func_ov245_020d62f0(void);
extern void func_ov245_020d6448(void);
extern void func_ov245_020d65fc(void);
extern void func_ov245_020d66fc(void);
extern void func_ov245_020d6998(void);
extern void func_ov245_020d6d0c(void);
extern void func_ov245_020d6fe8(void);
extern void func_ov245_020d70b0(void);

void func_ov245_020d5e44(int self) {
    int *ctx;

    ctx = *(int **)(self + 4);
    if (*(signed char *)(ctx[0] + 0x1c7) != -1) {
        *(signed char *)(ctx[0] + 0x1c6) = *(signed char *)(ctx[0] + 0x1c7);
        ((Hw60 *)(ctx[0] + 0x60))->hi &= ~0xce;
        *(unsigned short *)(ctx[0] + 0x1ae) &= ~1;
        ((B8 *)(*(int *)(ctx[0] + 0x388) + 8))->f |= 1;

        switch (*(signed char *)(ctx[0] + 0x1c6)) {
        case 0:
            func_0203c634(self, 1, func_ov245_020d607c);
            break;
        case 1:
            func_0203c634(self, 1, func_ov245_020d60e0);
            break;
        case 2:
            func_0203c634(self, 1, func_ov245_020d62f0);
            break;
        case 4:
            func_0203c634(self, 1, func_ov245_020d6448);
            break;
        case 5:
            func_0203c634(self, 1, func_ov245_020d65fc);
            break;
        case 6:
            func_0203c634(self, 1, func_ov245_020d66fc);
            break;
        case 7:
            func_0203c634(self, 1, func_ov245_020d6998);
            break;
        case 8:
            func_0203c634(self, 1, func_ov245_020d6d0c);
            break;
        case 3:
            func_0203c634(self, 1, func_ov245_020d6fe8);
            break;
        case 9:
            func_0203c634(self, 1, func_ov245_020d70b0);
            break;
        }
    }

    *(signed char *)(ctx[0] + 0x1c7) = -1;
}

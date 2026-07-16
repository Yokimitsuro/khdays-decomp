/* func_ov207_020d115c -- ov206's move dispatcher, the plainest of the family: -1 at ctx[0]+0x1c7
 * means nothing queued, the id is copied to +0x1c6 and it is that copy the switch reads, and the
 * slot is cleared on every path.
 *
 * The reset drops 0xce from the hw60 hi-byte and bit 0 of the halfword at +0x1ae, then sets bit 0
 * on the sub-object at ctx[0]+0x3ac and bits 0-1 on the one at +0x3b0.
 *
 * Case 3 is out of order (after 7), as in every other dispatcher in this codebase -- the table is
 * index-ordered but the bodies follow source order.
 *
 * The hw60 write HAS the lsl#0x10/lsr#0x10 trunc pair -> bitfield form; the +8 fields are
 * byte-in-word. See codegen-cracks.md. */

typedef struct {
    unsigned short lo : 8;
    unsigned short hi : 8;
} Hw60;

typedef struct {
    unsigned f : 8;
} B8;

extern void func_0203c634(int self, int slot, void (*cb)(void));
extern void func_ov207_020d1458(void);
extern void func_ov207_020d153c(void);
extern void func_ov207_020d1700(void);
extern void func_ov207_020d17b4(void);
extern void func_ov207_020d1cd8(void);
extern void func_ov207_020d2494(void);
extern void func_ov207_020d29fc(void);
extern void func_ov207_020d2bd8(void);
extern void func_ov207_020d2cc8(void);
extern void func_ov207_020d31f0(void);
extern void func_ov207_020d3268(void);
extern void func_ov207_020d35fc(void);
extern void func_ov207_020d40b4(void);

void func_ov207_020d115c(int self) {
    int *ctx;

    ctx = *(int **)(self + 4);
    if (*(signed char *)(ctx[0] + 0x1c7) != -1) {
        *(signed char *)(ctx[0] + 0x1c6) = *(signed char *)(ctx[0] + 0x1c7);
        ((Hw60 *)(ctx[0] + 0x60))->hi &= ~0xce;
        *(unsigned short *)(ctx[0] + 0x1ae) &= ~1;
        ((B8 *)(*(int *)(ctx[0] + 0x3ac) + 8))->f |= 1;
        ((B8 *)(*(int *)(ctx[0] + 0x3b0) + 8))->f |= 3;

        switch (*(signed char *)(ctx[0] + 0x1c6)) {
        case 0:
            func_0203c634(self, 1, func_ov207_020d1458);
            break;
        case 1:
            func_0203c634(self, 1, func_ov207_020d153c);
            break;
        case 2:
            func_0203c634(self, 1, func_ov207_020d1700);
            break;
        case 4:
            func_0203c634(self, 1, func_ov207_020d17b4);
            break;
        case 5:
            func_0203c634(self, 1, func_ov207_020d1cd8);
            break;
        case 6:
            func_0203c634(self, 1, func_ov207_020d2494);
            break;
        case 7:
            func_0203c634(self, 1, func_ov207_020d29fc);
            break;
        case 3:
            func_0203c634(self, 1, func_ov207_020d2bd8);
            break;
        case 8:
            func_0203c634(self, 1, func_ov207_020d2cc8);
            break;
        case 9:
            func_0203c634(self, 1, func_ov207_020d31f0);
            break;
        case 10:
            func_0203c634(self, 1, func_ov207_020d3268);
            break;
        case 11:
            func_0203c634(self, 1, func_ov207_020d35fc);
            break;
        case 12:
            func_0203c634(self, 1, func_ov207_020d40b4);
            break;
        }
    }

    *(signed char *)(ctx[0] + 0x1c7) = -1;
}

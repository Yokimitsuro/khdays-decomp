/* func_ov275_020d2f7c -- ov206's move dispatcher, the plainest of the family: -1 at ctx[0]+0x1c7
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
extern void func_ov275_020d3278(void);
extern void func_ov275_020d335c(void);
extern void func_ov275_020d3520(void);
extern void func_ov275_020d35d4(void);
extern void func_ov275_020d3af8(void);
extern void func_ov275_020d42b8(void);
extern void func_ov275_020d4820(void);
extern void func_ov275_020d49fc(void);
extern void func_ov275_020d4aec(void);
extern void func_ov275_020d5014(void);
extern void func_ov275_020d508c(void);
extern void func_ov275_020d5420(void);
extern void func_ov275_020d5ed8(void);

void func_ov275_020d2f7c(int self) {
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
            func_0203c634(self, 1, func_ov275_020d3278);
            break;
        case 1:
            func_0203c634(self, 1, func_ov275_020d335c);
            break;
        case 2:
            func_0203c634(self, 1, func_ov275_020d3520);
            break;
        case 4:
            func_0203c634(self, 1, func_ov275_020d35d4);
            break;
        case 5:
            func_0203c634(self, 1, func_ov275_020d3af8);
            break;
        case 6:
            func_0203c634(self, 1, func_ov275_020d42b8);
            break;
        case 7:
            func_0203c634(self, 1, func_ov275_020d4820);
            break;
        case 3:
            func_0203c634(self, 1, func_ov275_020d49fc);
            break;
        case 8:
            func_0203c634(self, 1, func_ov275_020d4aec);
            break;
        case 9:
            func_0203c634(self, 1, func_ov275_020d5014);
            break;
        case 10:
            func_0203c634(self, 1, func_ov275_020d508c);
            break;
        case 11:
            func_0203c634(self, 1, func_ov275_020d5420);
            break;
        case 12:
            func_0203c634(self, 1, func_ov275_020d5ed8);
            break;
        }
    }

    *(signed char *)(ctx[0] + 0x1c7) = -1;
}

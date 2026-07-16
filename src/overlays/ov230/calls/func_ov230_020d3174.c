/* func_ov230_020d3174 -- ov230's move dispatcher. The plain family shape: -1 at ctx[0]+0x1c7 means
 * nothing queued, the id is copied to +0x1c6 and it is that copy the switch reads, and the slot is
 * cleared on every path.
 *
 * The reset drops 0xc6 from the hw60 hi-byte and bits 0-1 of the halfword at +0x1ae, then sets bit
 * 0 on the sub-object at ctx[0]+0x3ac.
 *
 * Case 11 is absent from the switch, and case 3 is out of order (after 10) as everywhere else.
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
extern void func_ov230_020d34f4(void);
extern void func_ov230_020d35e8(void);
extern void func_ov230_020d38f4(void);
extern void func_ov230_020d3ac0(void);
extern void func_ov230_020d3fc4(void);
extern void func_ov230_020d45b0(void);
extern void func_ov230_020d4960(void);
extern void func_ov230_020d4c00(void);
extern void func_ov230_020d4de8(void);
extern void func_ov230_020d50e0(void);
extern void func_ov230_020d58ac(void);
extern void func_ov230_020d5994(void);
extern void func_ov230_020d5af0(void);

void func_ov230_020d3174(int self) {
    int *ctx;

    ctx = *(int **)(self + 4);
    if (*(signed char *)(ctx[0] + 0x1c7) != -1) {
        *(signed char *)(ctx[0] + 0x1c6) = *(signed char *)(ctx[0] + 0x1c7);
        ((Hw60 *)(ctx[0] + 0x60))->hi &= ~0xc6;
        *(unsigned short *)(ctx[0] + 0x1ae) &= ~3;
        ((B8 *)(*(int *)(ctx[0] + 0x3ac) + 8))->f |= 1;

        switch (*(signed char *)(ctx[0] + 0x1c6)) {
        case 0:
            func_0203c634(self, 1, func_ov230_020d34f4);
            break;
        case 1:
            func_0203c634(self, 1, func_ov230_020d35e8);
            break;
        case 2:
            func_0203c634(self, 1, func_ov230_020d38f4);
            break;
        case 4:
            func_0203c634(self, 1, func_ov230_020d3ac0);
            break;
        case 5:
            func_0203c634(self, 1, func_ov230_020d3fc4);
            break;
        case 6:
            func_0203c634(self, 1, func_ov230_020d45b0);
            break;
        case 7:
            func_0203c634(self, 1, func_ov230_020d4960);
            break;
        case 8:
            func_0203c634(self, 1, func_ov230_020d4c00);
            break;
        case 9:
            func_0203c634(self, 1, func_ov230_020d4de8);
            break;
        case 10:
            func_0203c634(self, 1, func_ov230_020d50e0);
            break;
        case 3:
            func_0203c634(self, 1, func_ov230_020d58ac);
            break;
        case 12:
            func_0203c634(self, 1, func_ov230_020d5994);
            break;
        case 13:
            func_0203c634(self, 1, func_ov230_020d5af0);
            break;
        }
    }

    *(signed char *)(ctx[0] + 0x1c7) = -1;
}

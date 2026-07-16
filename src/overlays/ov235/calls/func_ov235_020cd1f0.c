/* func_ov235_020cd1f0 -- ov235's move dispatcher.
 *
 * Its reset zeroes more than the others: the byte at ctx+0x64 and the word at ctx+0x80, and then a
 * three-word block on the owner at +0x64/+0x68/+0x6c seeded {0, 0x1800, 0} -- a vector whose
 * middle component is the only one set, so 0x1800 is a height or a Y speed.
 *
 * The "nothing queued" case RETURNS outright (a predicated `popeq`) rather than falling into the
 * shared -1 store, as in ov208/ov213/ov257.
 *
 * Case 3 is out of order (last) as everywhere else.
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
extern void func_ov235_020cd4d4(void);
extern void func_ov235_020cd5d8(void);
extern void func_ov235_020cd958(void);
extern void func_ov235_020cdd30(void);
extern void func_ov235_020ce2c4(void);
extern void func_ov235_020ce59c(void);
extern void func_ov235_020ce820(void);
extern void func_ov235_020ceaa0(void);
extern void func_ov235_020cf5f0(void);
extern void func_ov235_020cfb1c(void);
extern void func_ov235_020cff80(void);
extern void func_ov235_020d08d4(void);
extern void func_ov235_020d19cc(void);

void func_ov235_020cd1f0(int self) {
    int *ctx;
    int owner;

    ctx = *(int **)(self + 4);
    if (*(signed char *)(ctx[0] + 0x1c7) == -1) {
        return;
    }

    *(signed char *)(ctx[0] + 0x1c6) = *(signed char *)(ctx[0] + 0x1c7);
    *(unsigned char *)((char *)ctx + 0x64) = 0;
    ctx[0x20] = 0;

    /* The three stores go through a local. Written as `*(int *)(ctx[0] + 0x64) = 0;` etc. mwcc
     * re-reads ctx[0] before each one -- a store through ctx[0] could alias *ctx itself, so it
     * cannot keep the value. The ROM loads it once; a local says the address is fixed. */
    owner = ctx[0];
    *(int *)(owner + 0x64) = 0;
    *(int *)(owner + 0x68) = 0x1800;
    *(int *)(owner + 0x6c) = 0;
    ((Hw60 *)(ctx[0] + 0x60))->hi &= ~0xde;
    *(unsigned short *)(ctx[0] + 0x1ae) &= ~1;
    ((B8 *)(*(int *)(ctx[0] + 0x39c) + 8))->f |= 1;

    switch (*(signed char *)(ctx[0] + 0x1c6)) {
    case 0:
        func_0203c634(self, 1, func_ov235_020cd4d4);
        break;
    case 1:
        func_0203c634(self, 1, func_ov235_020cd5d8);
        break;
    case 2:
        func_0203c634(self, 1, func_ov235_020cd958);
        break;
    case 4:
        func_0203c634(self, 1, func_ov235_020cdd30);
        break;
    case 5:
        func_0203c634(self, 1, func_ov235_020ce2c4);
        break;
    case 6:
        func_0203c634(self, 1, func_ov235_020ce59c);
        break;
    case 7:
        func_0203c634(self, 1, func_ov235_020ce820);
        break;
    case 8:
        func_0203c634(self, 1, func_ov235_020ceaa0);
        break;
    case 9:
        func_0203c634(self, 1, func_ov235_020cf5f0);
        break;
    case 10:
        func_0203c634(self, 1, func_ov235_020cfb1c);
        break;
    case 11:
        func_0203c634(self, 1, func_ov235_020cff80);
        break;
    case 12:
        func_0203c634(self, 1, func_ov235_020d08d4);
        break;
    case 3:
        func_0203c634(self, 1, func_ov235_020d19cc);
        break;
    }

    *(signed char *)(ctx[0] + 0x1c7) = -1;
}

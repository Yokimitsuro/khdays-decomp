/* func_ov257_020cd370 -- ov257's move dispatcher.
 *
 * Case 1 rewrites the id to 2 and FALLS THROUGH into case 2 -- the case-2 table entry points 8
 * bytes into case 1's body, past the store. Unlike ov213's equivalent, this store is NOT dead: the
 * copy at +0x1c6 is what everything downstream reads, and only +0x1c7 gets cleared at the end. So
 * move 1 really does become move 2.
 *
 * The "nothing queued" case RETURNS outright (a predicated `popeq`) rather than falling into the
 * shared -1 store, as in ov208/ov213.
 *
 * The reset clears the byte at ctx+0x77 and the word at ctx+0x58, drops 0xce from the hw60
 * hi-byte and bit 0 of the halfword at +0x1ae, and sets bit 0 on the sub-object at ctx[0]+0x3b4.
 *
 * The hw60 write HAS the lsl#0x10/lsr#0x10 trunc pair -> bitfield form; the +8 field is
 * byte-in-word. See codegen-cracks.md.
 *
 * ------------------------------------------------------------------------------------------
 * UNFINISHED, not a tie: 528 vs 524 -- ONE instruction. mwcc hoists a partial address
 * (\dd r1,r3,#0xc6\) out of the switch because +0x1c6 is written in TWO places (the reset copy
 * and case 1s rewrite) and it CSEs the address; the ROM just uses \strb r1,[r2,#0x1c6]\ in the
 * body off the ctx[0] it already has. Everything else is byte-identical.
 *
 * Worth trying: model ctx[0] as a struct so the two writes are field accesses rather than pointer
 * arithmetic (that is the fix that worked on func_ov208_020d0138 and func_ov000_0205721c). Note
 * the ROM reaches the SAME field two ways depending on the instruction -- \dd rN,r2,#0x100 ;
 * ldrsb [rN,#0xc7]\ to read (ldrsb has an 8-bit offset) but \strb r1,[r2,#0x1c6]\ to write (strb
 * has 12) -- so the struct has to survive both. Every other dispatcher matched with the raw form,
 * so this is specific to having two writers. */

typedef struct {
    unsigned short lo : 8;
    unsigned short hi : 8;
} Hw60;

typedef struct {
    unsigned f : 8;
} B8;

extern void func_0203c634(int self, int slot, void (*cb)(void));
extern void func_ov257_020cd60c(void);
extern void func_ov257_020cd6f0(void);
extern void func_ov257_020cda48(void);
extern void func_ov257_020ce04c(void);
extern void func_ov257_020ce308(void);
extern void func_ov257_020ce594(void);
extern void func_ov257_020ce814(void);
extern void func_ov257_020cf3f8(void);
extern void func_ov257_020cfb50(void);
extern void func_ov257_020d003c(void);
extern void func_ov257_020d096c(void);
extern void func_ov257_020d1bf8(void);
extern void func_ov257_020d2474(void);

void func_ov257_020cd370(int self) {
    int *ctx;

    ctx = *(int **)(self + 4);
    if (*(signed char *)(ctx[0] + 0x1c7) == -1) {
        return;
    }

    *(unsigned char *)((char *)ctx + 0x77) = 0;
    ctx[0x16] = 0;
    ((Hw60 *)(ctx[0] + 0x60))->hi &= ~0xce;
    *(unsigned short *)(ctx[0] + 0x1ae) &= ~1;
    ((B8 *)(*(int *)(ctx[0] + 0x3b4) + 8))->f |= 1;
    *(signed char *)(ctx[0] + 0x1c6) = *(signed char *)(ctx[0] + 0x1c7);

    switch (*(signed char *)(ctx[0] + 0x1c6)) {
    case 0:
        func_0203c634(self, 1, func_ov257_020cd60c);
        break;
    case 1:
        *(signed char *)(ctx[0] + 0x1c6) = 2;
        /* fall through */
    case 2:
        func_0203c634(self, 1, func_ov257_020cd6f0);
        break;
    case 4:
        func_0203c634(self, 1, func_ov257_020cda48);
        break;
    case 5:
        func_0203c634(self, 1, func_ov257_020ce04c);
        break;
    case 6:
        func_0203c634(self, 1, func_ov257_020ce308);
        break;
    case 7:
        func_0203c634(self, 1, func_ov257_020ce594);
        break;
    case 8:
        func_0203c634(self, 1, func_ov257_020ce814);
        break;
    case 9:
        func_0203c634(self, 1, func_ov257_020cf3f8);
        break;
    case 10:
        func_0203c634(self, 1, func_ov257_020cfb50);
        break;
    case 11:
        func_0203c634(self, 1, func_ov257_020d003c);
        break;
    case 12:
        func_0203c634(self, 1, func_ov257_020d096c);
        break;
    case 13:
        func_0203c634(self, 1, func_ov257_020d1bf8);
        break;
    case 3:
        func_0203c634(self, 1, func_ov257_020d2474);
        break;
    }

    *(signed char *)(ctx[0] + 0x1c7) = -1;
}

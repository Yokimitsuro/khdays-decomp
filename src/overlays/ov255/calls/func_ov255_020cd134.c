/* func_ov255_020cd134 -- ov255's move dispatcher.
 *
 * Case 1 rewrites the id to 2 and FALLS THROUGH into case 2, exactly as func_ov257_020cd370 does.
 * The rewrite lands in +0x1c6 (the copy everything downstream reads), and only +0x1c7 is cleared
 * at the end, so move 1 genuinely becomes move 2.
 *
 * The "nothing queued" case RETURNS outright (a predicated `popeq`). The reset also clears the
 * byte at ctx+0x64 and the word at ctx+0x4c, and -- unlike most of the family -- copies the id to
 * +0x1c6 AFTER the flag work rather than before.
 *
 * Case 3 is last, as everywhere else in the family.
 *
 * The move slots are modelled as struct fields because +0x1c6 has TWO writers (the reset copy and
 * case 1's rewrite). With pointer arithmetic mwcc splits the 0x1c6 offset and hoists the partial
 * address `ctx[0]+0xc6` into the switch header, to reach the store as [rN,#0x100]; the ROM instead
 * keeps ctx[0] itself live and stores straight to [rN,#0x1c6] (strb's 12-bit immediate covers it,
 * while the ldrsb read needs the +0x100 add for its 8-bit one). The struct gives the store its own
 * base and the hoist goes away. See codegen-cracks.md. */

typedef struct {
    unsigned short lo : 8;
    unsigned short hi : 8;
} Hw60;

typedef struct {
    unsigned f : 8;
} B8;

typedef struct {
    char reserved[0x1c6];
    signed char cur;
    signed char queued;
} Owner;

extern void func_0203c634(int self, int slot, void (*cb)(void));
extern void func_ov255_020cd3b8(void);
extern void func_ov255_020cd49c(void);
extern void func_ov255_020cd7f4(void);
extern void func_ov255_020cdcd4(void);
extern void func_ov255_020cdfd8(void);
extern void func_ov255_020ce258(void);
extern void func_ov255_020ce4d8(void);
extern void func_ov255_020cf1c0(void);
extern void func_ov255_020cf914(void);
extern void func_ov255_020cfdb8(void);
extern void func_ov255_020d0710(void);
extern void func_ov255_020d0d04(void);

void func_ov255_020cd134(int self) {
    int *ctx;

    ctx = *(int **)(self + 4);
    if (((Owner *)ctx[0])->queued == -1) {
        return;
    }

    *(unsigned char *)((char *)ctx + 0x64) = 0;
    ctx[0x13] = 0;
    ((Hw60 *)(ctx[0] + 0x60))->hi &= ~0xce;
    *(unsigned short *)(ctx[0] + 0x1ae) &= ~1;
    ((B8 *)(*(int *)(ctx[0] + 0x394) + 8))->f |= 1;
    ((Owner *)ctx[0])->cur = ((Owner *)ctx[0])->queued;

    switch (((Owner *)ctx[0])->cur) {
    case 0:
        func_0203c634(self, 1, func_ov255_020cd3b8);
        break;
    case 1:
        ((Owner *)ctx[0])->cur = 2;
        /* fall through */
    case 2:
        func_0203c634(self, 1, func_ov255_020cd49c);
        break;
    case 4:
        func_0203c634(self, 1, func_ov255_020cd7f4);
        break;
    case 5:
        func_0203c634(self, 1, func_ov255_020cdcd4);
        break;
    case 6:
        func_0203c634(self, 1, func_ov255_020cdfd8);
        break;
    case 7:
        func_0203c634(self, 1, func_ov255_020ce258);
        break;
    case 8:
        func_0203c634(self, 1, func_ov255_020ce4d8);
        break;
    case 9:
        func_0203c634(self, 1, func_ov255_020cf1c0);
        break;
    case 10:
        func_0203c634(self, 1, func_ov255_020cf914);
        break;
    case 11:
        func_0203c634(self, 1, func_ov255_020cfdb8);
        break;
    case 12:
        func_0203c634(self, 1, func_ov255_020d0710);
        break;
    case 3:
        func_0203c634(self, 1, func_ov255_020d0d04);
        break;
    }

    ((Owner *)ctx[0])->queued = -1;
}

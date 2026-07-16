/* func_ov267_020d2128 -- ov212's move dispatcher. The family shape (test ctx[0]+0x1c7 against -1,
 * reset, copy the id to +0x1c6, dense jump table of c634 entries, clear the slot) with two things
 * the others do not have:
 *
 *  - func_ov267_020d1f0c gets a veto, and its early-out RETURNS rather than falling to the tail,
 *    so a vetoed move stays queued for the next tick;
 *  - the three sub-objects at ctx[0]+0x4cc are cycled: slot 0 gets bit 0 SET and slots 1-2 get it
 *    cleared, so this picks which of the three is live.
 *
 * Moves 6, 7 and 8 add 8 to the halfword at ctx[0]+0x1b0; everything else overwrites it from
 * ctx+0x58 -- so those three share a property the rest do not.
 *
 * ★ That three-way test MUST be a `switch`, not an `if (m == 6 || m == 7 || m == 8)`. The values
 * are contiguous, so the || chain gets range-optimised into `sub r1,#6 ; cmp r1,#2` (4 bytes
 * short), and reordering them (6,8,7) does not help -- mwcc sorts the set. Written the != way
 * round the compares come out right but the arms swap, so the short one gets if-converted. A small
 * dense switch gives exactly the ROM's `cmp #6 ; cmpne #7 ; cmpne #8 ; bne`. See
 * codegen-cracks.md.
 *
 * The slot table is modelled as a real array so mwcc keeps the ROM's scaled index
 * (`add r0,r0,r1,lsl #2 ; ldr r3,[r0,#0x4cc]`) instead of walking a pointer; see
 * codegen-cracks.md. */

typedef struct {
    unsigned short lo : 8;
    unsigned short hi : 8;
} Hw60;

typedef struct {
    unsigned f : 8;
} B8;

typedef struct {
    char reserved[0x4cc];
    int slots[3];
} Owner;

extern int func_ov267_020d1f0c(int self);
extern void func_ov022_020ad8e0(int a, int b);
extern void func_0203c634(int self, int slot, void (*cb)(void));
extern void func_ov267_020d25b4(void);
extern void func_ov267_020d274c(void);
extern void func_ov267_020d2a00(void);
extern void func_ov267_020d2bcc(void);
extern void func_ov267_020d2f78(void);
extern void func_ov267_020d31b4(void);
extern void func_ov267_020d3484(void);
extern void func_ov267_020d374c(void);
extern void func_ov267_020d39a0(void);
extern void func_ov267_020d3ac8(void);
extern void func_ov267_020d3be4(void);
extern void func_ov267_020d3ec8(void);
extern void func_ov267_020d423c(void);
extern void func_ov267_020d433c(void);
extern void func_ov267_020d44c8(void);

void func_ov267_020d2128(int self) {
    int *ctx;
    int i;

    ctx = *(int **)(self + 4);
    if (*(signed char *)(ctx[0] + 0x1c7) != -1) {
        if (func_ov267_020d1f0c(self) == 0) {
            return;
        }

        *(signed char *)(ctx[0] + 0x1c6) = *(signed char *)(ctx[0] + 0x1c7);
        ((Hw60 *)(ctx[0] + 0x60))->hi &= ~0xc6;
        *(unsigned short *)(ctx[0] + 0x1ae) &= ~3;

        for (i = 0; i < 3; i++) {
            if (i == 0) {
                ((B8 *)(((Owner *)ctx[0])->slots[i] + 8))->f |= 1;
            } else {
                ((B8 *)(((Owner *)ctx[0])->slots[i] + 8))->f &= ~1;
            }
        }

        if (ctx[3] != 0) {
            func_ov022_020ad8e0(ctx[3], 0);
            ctx[3] = 0;
        }

        /* Written as a != chain: 6,7,8 are contiguous, and the == form gets range-optimised into
         * `sub r1,#6 ; cmp r1,#2`, where the ROM has three explicit `cmp`/`cmpne`. */
        switch (*(signed char *)(ctx[0] + 0x1c6)) {
        case 6:
        case 7:
        case 8:
            *(unsigned short *)(ctx[0] + 0x1b0) |= 8;
            break;
        default:
            *(unsigned short *)(ctx[0] + 0x1b0) = *(unsigned short *)((char *)ctx + 0x58);
            break;
        }

        switch (*(signed char *)(ctx[0] + 0x1c6)) {
        case 0:
            func_0203c634(self, 1, func_ov267_020d25b4);
            break;
        case 1:
            func_0203c634(self, 1, func_ov267_020d274c);
            break;
        case 2:
            func_0203c634(self, 1, func_ov267_020d2a00);
            break;
        case 4:
            func_0203c634(self, 1, func_ov267_020d2bcc);
            break;
        case 5:
            func_0203c634(self, 1, func_ov267_020d2f78);
            break;
        case 6:
            func_0203c634(self, 1, func_ov267_020d31b4);
            break;
        case 7:
            func_0203c634(self, 1, func_ov267_020d3484);
            break;
        case 8:
            func_0203c634(self, 1, func_ov267_020d374c);
            break;
        case 9:
            func_0203c634(self, 1, func_ov267_020d39a0);
            break;
        case 10:
            func_0203c634(self, 1, func_ov267_020d3ac8);
            break;
        case 11:
            func_0203c634(self, 1, func_ov267_020d3be4);
            break;
        case 12:
            func_0203c634(self, 1, func_ov267_020d3ec8);
            break;
        case 3:
            func_0203c634(self, 1, func_ov267_020d423c);
            break;
        case 13:
            func_0203c634(self, 1, func_ov267_020d433c);
            break;
        case 14:
            func_0203c634(self, 1, func_ov267_020d44c8);
            break;
        }
    }

    *(signed char *)(ctx[0] + 0x1c7) = -1;
}

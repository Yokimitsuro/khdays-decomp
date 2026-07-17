/*
 * func_ov212_020cffd0 -- UNFINISHED. 292/292 bytes, 73/73 instructions.
 * x3 family (ov266/ov267) -> worth 3. Two scheduling slots apart; every opcode,
 * operand, constant, branch and call is right.
 *
 * WHAT IT DOES: acquire a target and face it. Ask ov107_020cab14 for one and cache it
 * at owner+0x5a8; with none, latch slot 2 and advance. Otherwise measure the vector
 * from the anchor (ctx[2]) to the target (target+0x190), build the unit facing
 * {sin, 0, cos} from the STORED heading (ctx+0x34) into ctx+0x28, scale it by 0x800,
 * kick animation 0xd, clear the phase timer and the two one-shot bytes, and chain to
 * 020d00f4.
 *
 * ★ TWO REAL FINDINGS, both preserved in the C -- do not "clean them up":
 *  1. **The atan2 result is DISCARDED.** The ROM calls func_020050b4(d.x, d.z) at
 *     +0x06c and overwrites r0 at +0x074 without reading it, then converts the STORED
 *     heading ctx+0x34 instead. So the freshly measured angle is computed and thrown
 *     away. This is very likely a game bug (they meant to store it) and it is the same
 *     shape as the discarded VEC_DotProduct in ov231_020cdd3c. Flagged for the port,
 *     reproduced faithfully, NOT fixed.
 *  2. **`mov r0, #0x800` does double duty**: it is the Q12 rounding constant for the
 *     angle conversion's `adc r1, r3, r0` AND the first argument to func_01ffa724 ~18
 *     instructions later. mwcc CSEs it exactly the same way, so this part is already
 *     right -- do not "fix" it by splitting the constant.
 *
 * THE DIFF -- two independent scheduler choices, nothing else:
 *   a) ROM: `mov r0,#0x800` then `adds r1,ip,#0`. mine: the two swapped. The ROM fills
 *      the slot right after `mla r3,r1,r0,r3` kills r0; mwcc waits one instruction.
 *   b) the sin/cos block: the ROM does BOTH `ldrsh` and then all three stores; mwcc
 *      sinks the second `ldrsh` below the first two stores (and holds the table base
 *      in ip where the ROM uses r3).
 *
 * PRE-PARK CHECKLIST -- all four run:
 *  1. --thumb: ARM gives the exact 292/292.
 *  2. Arity, checked against real (non-asm_stub) call sites: ov107_020cab14(obj,0) 2 ·
 *     VEC_Subtract(a,b,out) 3 · 020050b4(dx,dz) 2 · 01ffa724(scale,v,out) 3 ·
 *     ov107_020c9264(a,b,c) 3 · 0203c634(self,slot,cb) 3. All agree with the ROM's own
 *     register setup, including r0=0x800 being live at the 01ffa724 call.
 *  3. No constant is in the wrong register (see finding 2 -- 0x800 is where it belongs).
 *  4. Diff read back: two moved instructions, same operands.
 *
 * RULED OUT (6 spellings, all still 292/292 with the first diff pinned at 0x8c):
 *   both table loads hoisted into locals before the stores (block-scoped)
 *   ... hoisted in a single declaration statement
 *   0x800 shared through an explicit `int sc = 0x800` local used by BOTH the rounding
 *     (`+ ((long long)sc << 32)`) and the call -- declared at the top
 *   ... and declared immediately before the conversion
 *   the target re-read inline vs held in a local (`tgt`)
 *   ANG2IDX as a macro vs spelled out
 *
 * NEXT STEP: both diffs are the scheduler choosing a different (legal) slot for a
 * ready instruction. I have no source-level lever for either. Do NOT file this as a
 * "scheduling tie" and stop -- that label has been wrong ~20 times in this project;
 * three of today's four cracks started life labelled exactly that.
 */
struct vec3 { int x, y, z; };

extern int *func_ov107_020cab14(int a, int b);
extern int VEC_Subtract(void *a, void *b, void *out);
extern int func_020050b4(int a, int b);
extern void func_01ffa724(int s, struct vec3 *v, struct vec3 *out);
extern void func_ov107_020c9264(int a, int b, int c);
extern void func_0203c634(void *self, int idx, void *cb);
extern void func_ov212_020d00f4(void);
extern short data_0203d210[];

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)

void func_ov212_020cffd0(void *self) {
    int *ctx = *(int **)((char *)self + 4);
    struct vec3 d;
    unsigned int idx;
    int tgt;

    *(int *)(*ctx + 0x5a8) = (int)func_ov107_020cab14(*ctx, 0);
    tgt = *(int *)(*ctx + 0x5a8);
    if (tgt == 0) {
        *(char *)(*ctx + 0x1c7) = 2;
        func_0203c634(self, *(signed char *)((char *)self + 0x20), 0);
        return;
    }
    VEC_Subtract((char *)tgt + 0x190, (void *)ctx[2], &d);
    func_020050b4(d.x, d.z);
    idx = ANG2IDX(ctx[0xd]);
    ctx[0xa] = data_0203d210[idx * 2];
    ctx[0xb] = 0;
    ctx[0xc] = data_0203d210[idx * 2 + 1];
    func_01ffa724(0x800, (struct vec3 *)(ctx + 0xa), (struct vec3 *)(ctx + 0xa));
    func_ov107_020c9264(*ctx, 0xd, 0);
    ctx[0x10] = 0;
    *(char *)((char *)ctx + 0x5a) = 0;
    *(char *)((char *)ctx + 0x5b) = 0;
    func_0203c634(self, *(signed char *)((char *)self + 0x20), func_ov212_020d00f4);
}

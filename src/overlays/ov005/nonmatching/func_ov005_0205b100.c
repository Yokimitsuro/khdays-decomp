/*
 * func_ov005_0205b100 -- UNFINISHED. 476/476 bytes, 119/119 instructions.
 * x4 family (ov008_0208e66c / ov025_020b35d0 / ov026_02090ed4) -> worth 4.
 * ONE scratch register apart; every other byte is right, including the whole
 * 20-entry jump table.
 *
 * WHAT IT DOES: remap a character code for the active language. Given a message, take
 * its code (+0x14), let the sink flush anything pending, ask 0205896c which language is
 * active, and run the matching per-language remap. If the remap changed nothing, hand
 * back the message's existing glyph (+0x10); otherwise emit the remapped code through
 * the sink (self[1](self, 0x15, code, 0xe)) and return the glyph the sink produced.
 *
 * ★ SOLVED, and it is the whole reason this landed at the exact size on the first
 * compile -- the CASE ORDER. The ROM's dispatch is a dense jump table
 * (`cmp r0,#0x13 ; addls pc,pc,r0,lsl #2` + 20 branches), so the table order is fixed by
 * the case VALUES, but the case BODIES are laid out in source order. Reading the body
 * addresses off the disassembly gives the source order directly, and it is NOT 0..19 --
 * it is the order of the remap functions themselves (02058988, 02058bb4, 02058de0, ...
 * i.e. RemapCharCode00, 01, 02 ...), which maps to case values
 *   1, 6, 17, 18, 7, 8, 9, 10, 16, 11, {0,14,19}, 3, 5, 12, 4, 13, 2, 15, default.
 * Cases 0, 14 and 19 share a body (RemapCharCode10) and `default` falls through to
 * "unchanged". Write the switch in that order and the layout is free.
 *
 * THE DIFF, at 0x15 and nowhere else:
 *      ROM:   ldr r1,[r6] ; cmp r1,#0 ; ldr r1,[r6,#8] ; blx r1
 *      mine:  the same four with r0
 * Both registers are dead at that point (self went to r6 and msg to r5 in the first two
 * instructions), so both choices are legal; mwcc takes the lowest free register and the
 * ROM takes r1.
 *
 * PRE-PARK CHECKLIST -- all four run:
 *  1. --thumb: ARM gives the exact 476/476.
 *  2. Arity: the 18 remap functions take 1 arg each (the ROM sets only r0); 0205896c
 *     takes none; the two indirect calls are self[2]() with none and
 *     self[1](self, 0x15, out, 0xe) with four, all matching the ROM's register setup.
 *  3. No constant is in the wrong register.
 *  4. Diff read back: 119 vs 119, identical opcodes and operands; one register.
 *
 * RULED OUT (6 spellings, all still 476/476 with the diff pinned at 0x15):
 *   `self[0]` vs `*self` vs a `int h = self[0]` local vs a `int *h = (int *)self[0]` local
 *   the code read moved inside both arms of the if (-> 480, so it must precede the call:
 *     the ROM loads +0x14 at +0x018, BEFORE the blx, which is semantically load-bearing
 *     if the sink can touch the message)
 *   a real `struct Ctx` with typed function-pointer members instead of casts from int[]
 *     -- this is today's "declared type steers the caller" crack and it does NOT reach
 *     this choice (worth knowing: that crack is about ADDRESS materialisation, not about
 *     which scratch register a plain load lands in)
 *
 * NEXT STEP: the axis is which scratch register mwcc picks for a value that dies before
 * the next call, with r0 and r1 equally free. That is the ⛔ class in state.md and every
 * mechanical lever there is spent -- but do not treat that as a verdict: three of today's
 * four cracks came out of functions filed under exactly that label.
 */
extern int func_ov005_0205896c(void);
extern int func_ov005_02058988(int c);
extern int func_ov005_02058bb4(int c);
extern int func_ov005_02058de0(int c);
extern int func_ov005_0205900c(int c);
extern int func_ov005_02059238(int c);
extern int func_ov005_02059464(int c);
extern int func_ov005_02059690(int c);
extern int func_ov005_020598bc(int c);
extern int func_ov005_02059ae8(int c);
extern int func_ov005_02059d14(int c);
extern int func_ov005_02059f40(int c);
extern int func_ov005_0205a16c(int c);
extern int func_ov005_0205a398(int c);
extern int func_ov005_0205a5c4(int c);
extern int func_ov005_0205a7f0(int c);
extern int func_ov005_0205aa1c(int c);
extern int func_ov005_0205ac48(int c);
extern int func_ov005_0205ae74(int c);

int func_ov005_0205b100(int *self, int msg) {
    int code;
    int out;

    if (msg == 0) {
        return 0;
    }
    code = *(int *)(msg + 0x14);
    if (self[0] != 0) {
        ((void (*)(void))self[2])();
    }
    switch (func_ov005_0205896c()) {
    case 1:  out = func_ov005_02058988(code); break;
    case 6:  out = func_ov005_02058bb4(code); break;
    case 17: out = func_ov005_02058de0(code); break;
    case 18: out = func_ov005_0205900c(code); break;
    case 7:  out = func_ov005_02059238(code); break;
    case 8:  out = func_ov005_02059464(code); break;
    case 9:  out = func_ov005_02059690(code); break;
    case 10: out = func_ov005_020598bc(code); break;
    case 16: out = func_ov005_02059ae8(code); break;
    case 11: out = func_ov005_02059d14(code); break;
    case 0:
    case 14:
    case 19: out = func_ov005_02059f40(code); break;
    case 3:  out = func_ov005_0205a16c(code); break;
    case 5:  out = func_ov005_0205a398(code); break;
    case 12: out = func_ov005_0205a5c4(code); break;
    case 4:  out = func_ov005_0205a7f0(code); break;
    case 13: out = func_ov005_0205aa1c(code); break;
    case 2:  out = func_ov005_0205ac48(code); break;
    case 15: out = func_ov005_0205ae74(code); break;
    default: out = code; break;
    }
    if (out == code) {
        return *(int *)(msg + 0x10);
    }
    ((void (*)(int *, int, int, int))self[1])(self, 0x15, out, 0xe);
    return *(int *)(*self + 0x10);
}

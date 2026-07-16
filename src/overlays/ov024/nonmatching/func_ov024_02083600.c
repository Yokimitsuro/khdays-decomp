/* func_ov024_02083600 -- MobiClip: advance a stream's read position by one step.
 * The step is the stream's base stride (+0x54) plus whatever func_0202fae8 reports for this
 * tick. If taking another step of the same size would push the window (+0x5c) past the stream's
 * limit (+0x44), the step is rolled back and func_0202fb8c is given the stream to handle the
 * end -- so the position never actually crosses the limit. Either way the presentation lead is
 * recomputed before returning.
 *
 * NONMATCHING: register-allocation swap only -- 92/92 bytes, every instruction in the right
 * place, first diff at 0xd. The ROM computes `step` in place over the register that held +0x54
 * (ldr r1,[r4,#0x54]; add r1,r1,r0) and loads +0x5c into r2; mwcc mirrors the pair (p54 -> r2,
 * p5c -> r1) and puts step in a third register. Everything downstream is the same shift.
 *
 * The `pos` local is load-bearing and must stay: it is what makes the rollback re-load +0x5c
 * (ldr r2,[r4,#0x5c] at 0x38) instead of reusing the just-stored value. In the ROM the register
 * holding the new position is clobbered by the +0x44 load, so the reload is forced; writing the
 * update as a plain `*(int *)(stream + 0x5c) += step;` lets mwcc keep the value live and CSE the
 * reload away, which comes out 4 bytes short.
 * Tried and rejected: decl-order swap (pos/step), and computing step as f() then += 0x54.
 * Same diff at 0xd every time -- this is the regalloc-swap tie class. */
extern unsigned char func_0202fae8(int stream);
extern void func_0202fb8c(int stream);
extern void func_ov024_02083a9c(int stream);

int func_ov024_02083600(int stream) {
    int pos;
    int step;

    step = *(int *)(stream + 0x54) + func_0202fae8(stream);
    pos = *(int *)(stream + 0x5c) + step;
    *(int *)(stream + 0x5c) = pos;
    if (pos + step - *(int *)(stream + 0x54) > *(int *)(stream + 0x44)) {
        *(int *)(stream + 0x5c) -= step;
        func_0202fb8c(stream);
    }
    func_ov024_02083a9c(stream);
    return 1;
}

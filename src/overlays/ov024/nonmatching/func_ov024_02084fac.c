/* NONMATCHING: 28B vs 32B -- one instruction, the known dead-re-check tie. The ROM emits
 *     movs r4,r0 ; cmpne r4,#0 ; popeq {r4,pc}
 * where the `movs` has ALREADY set Z from r0, so the `cmpne` cannot change the flags and is
 * pure dead weight. mwcc 3.0/139 elides it (movs + popeq). Everything else is identical.
 * Same "our compiler is smarter" family as the redundant-orr/dead-narrowing entries in
 * references/deferred-ties.md. Not expressible in C: both the early-return and the
 * if-wrapped forms give the same two instructions.
 *
 * func_ov024_02084fac -- MobiClip: destroy a decoder context.
 * Releases the context's own buffers (func_ov024_02085140) and then the context itself.
 * A null context is a no-op. */
extern void func_ov024_02085140(int *ctx);
extern void WM_EndKeySharing_0x02085104(int *p);

void func_ov024_02084fac(int *ctx) {
    if (ctx != 0) {
        func_ov024_02085140(ctx);
        WM_EndKeySharing_0x02085104(ctx);
    }
}

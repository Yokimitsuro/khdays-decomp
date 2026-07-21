/* NON-MATCHING: constant-materialization tie (ROM derives the stored 0 from the loop counter).
 *
 * Reset: for both AI slots (pointer array at *node+0x384), clear the four state bytes at
 * +0xa8/+0xa9/+0xaa/+0xac, then re-arm the slot with follow-up 020d58d4.
 * node=*(ReactionAiNode**)(self+4).
 *
 * Semantically exact, but 4 bytes short: the ROM materializes the stored zero out of the loop
 * induction register and keeps two copies of it,
 *      mov r2,lr ; ... ; and r1,r2,#0xff ; strb r2,[e,#0xa9] ; strb r1,[e,#0xac] ; strb r1 ; strb r1
 * i.e. the first store uses the raw counter-derived 0 (r2) and the other three a byte-masked 0
 * (r1). Every spelling tried collapses that to a single `mov r1,#0` reused for all four stores
 * (1 instruction fewer). The split is an -O4 register-allocation artifact of reusing the live
 * induction value as the constant; it is not reachable from source, and the addressing half
 * (subscript `((int*)(*node+0x384))[i]` vs flat `*(int*)(*node+i*4+0x384)`) only moves which of
 * the two loads carries the +0x384 immediate, never the extra instruction. Since the sizes differ,
 * a build_sweep would be meaningless (it needs right-size, right-stream C). Left as the cleanest
 * semantic form.
 */

extern int func_0203c634(int self, int idx, void *handler);
extern void func_ov254_020d58d4(int self);

void func_ov254_020d5884(int self) {
    int *node = *(int **)(self + 4);
    int i;
    for (i = 0; i < 2; i++) {
        int e = ((int *)(*node + 0x384))[i];
        *(unsigned char *)(e + 0xa9) = 0;
        *(unsigned char *)(e + 0xac) = 0;
        *(unsigned char *)(e + 0xaa) = 0;
        *(unsigned char *)(e + 0xa8) = 0;
    }
    func_0203c634(self, *(signed char *)(self + 0x20), &func_ov254_020d58d4);
}

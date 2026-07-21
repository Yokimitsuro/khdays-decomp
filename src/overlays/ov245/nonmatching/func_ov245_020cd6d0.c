/* NON-MATCHING: constant-materialization + scheduling tie (0xff derived from a live 0).
 *
 * Reaction enter (gated on hw60 low bit): seed node[0xb]=0x4000, clear pActor+0x4c4, set
 * pActor+0x4d8=0xff, clear node+0x43 and node[0x11], seed node[0xd]=0x1000, copy the queued
 * reaction id (pActor+0x1c9, signed) into the active one (pActor+0x1c7), re-arm the slot.
 * node=*(ReactionAiNode**)(self+4); *node=pActor.
 *
 * The whole stream is byte-identical to the ROM except how the 0xff is formed and scheduled. The
 * ROM keeps the zero live in r2, hoists it above the *node reload, and derives 0xff from it:
 *      mov r2,#0 ; ldr r1,[ip] ; sub r3,r2,#1 ; str r2,[r1,#0x4c4] ; ldr r1,[ip] ; strb r3,...
 * mwcc constant-folds any 0xff/-1/(zero-1) spelling to a plain `mov r3,#0xff` emitted late:
 *      ldr r1,[ip] ; mov r2,#0 ; str r2,[r1,#0x4c4] ; ldr r1,[ip] ; mov r3,#0xff ; strb r3,...
 * Because the fold happens at compile time, `= 0xff`, `= -1` and a shared `int zero; zero-1` all
 * produce the same `mov`; deriving 0xff from a *runtime* zero register is an -O4 allocator choice
 * not reachable from source. build_sweep reproduces "17 off" on every 2.0/3.0 build. Same tie
 * class as ov254_020d5884 (constant reused from a live register). NB the reaction-id copy must be
 * written `*(char*) = *(char*)` (not unsigned) so mwcc keeps the ldrsb+add split the ROM uses,
 * rather than optimising to a single wide-offset ldrb.
 */

struct hw60 { unsigned short lo:8, hi:8; };

extern int func_0203c634(int self, int idx, void *handler);

void func_ov245_020cd6d0(int self) {
    int *node = *(int **)(self + 4);
    if ((((struct hw60 *)(*node + 0x60))->lo & 1) == 0) { return; }
    node[0xb] = 0x4000;
    *(int *)(*node + 0x4c4) = 0;
    *(unsigned char *)(*node + 0x4d8) = 0xff;
    *(unsigned char *)((char *)node + 0x43) = 0;
    node[0x11] = 0;
    node[0xd] = 0x1000;
    *(char *)(*node + 0x1c7) = *(char *)(*node + 0x1c9);
    func_0203c634(self, *(signed char *)(self + 0x20), 0);
}

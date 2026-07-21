/* NON-MATCHING: instruction-scheduling tie (one independent load reordered).
 *
 * Reaction: copy a 4-byte event payload from the shared table (+0x14), fire the actor's vtable
 * method at pActor+0x24 with it (if present), cancel action 6, clear the node flag at +0x74, then
 * re-arm the slot with follow-up 020d2a28. node=*(ReactionAiNode**)(self+4).
 *
 * The full instruction stream is byte-identical to the ROM EXCEPT the position of the node load
 * `ldr r4,[r5,#4]`. The ROM's list scheduler hoists it up to fill the load-use bubble after
 * `ldrh r0,[r1,#0x16]`:
 *      ldrh r2,[r1,#0x14] ; ldrh r0,[r1,#0x16] ; ldr r4,[r5,#4] ; add r1,sp,#0 ; strh r2 ; strh r0
 * mwcc instead fills that slot with the store-address setup and emits the node load after the
 * stores:
 *      ldrh r2,[r1,#0x14] ; ldrh r0,[r1,#0x16] ; add r1,sp,#0 ; strh r2 ; strh r0 ; ldr r4,[r5,#4]
 * Both are valid schedules; the tie-break differs. Source reordering only moves the node load
 * one slot the wrong way (node-first -> diff@0x10; local-first -> diff@0x14). build_sweep across
 * all 27 mwcc builds reproduces "14 off" on every 2.0/3.0 line (older 1.2/dsi lines miscompile
 * the size entirely), so no available compiler schedules it the ROM's way. Twin ov278_020d296c
 * ties identically.
 */

struct Pair16 { unsigned short a, b; };

extern int func_ov107_020c9264(int obj, int a, int b);
extern int func_0203c634(int self, int idx, void *handler);
extern void func_ov236_020d2a28(int self);
extern char data_ov236_020d63e8[];

void func_ov236_020d29b8(int self) {
    struct Pair16 local;
    int *node;
    void (*method)(int, void *, int);
    local = *(struct Pair16 *)(data_ov236_020d63e8 + 0x14);
    node = *(int **)(self + 4);
    method = *(void (**)(int, void *, int))(*node + 0x24);
    if (method != 0) {
        method(*node, &local, 4);
    }
    func_ov107_020c9264(*node, 6, 0);
    *(unsigned char *)((char *)node + 0x74) = 0;
    func_0203c634(self, *(signed char *)(self + 0x20), &func_ov236_020d2a28);
}

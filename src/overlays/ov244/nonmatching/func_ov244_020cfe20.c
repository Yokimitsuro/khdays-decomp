/* NON-MATCHING: register-allocation tie in the 2-halfword payload copy.
 *
 * Reaction: cancel action 1, copy a 4-byte event payload from the shared table (+4), fire the
 * actor's vtable method at pActor+0x24 with it (if present), clear node[7], then re-arm the slot
 * with follow-up 020cfe90. node=*(ReactionAiNode**)(self+4).
 *
 * Byte-identical to the ROM except which halfword of the payload lands in which scratch register.
 * The ROM loads the high half first (base pointer is in r0, and the low load reuses r0):
 *      ldrh r2,[r0,#6] ; ldrh r0,[r0,#4] ; strh r2,[sp,#2] ; strh r0,[sp]
 * The struct copy below sets up the &local pointer early (matching the ROM's add r1,sp,#0) but
 * loads the low half first:
 *      ldrh r2,[r0,#4] ; ldrh r0,[r0,#6] ; strh r2,[sp] ; strh r0,[sp,#2]     (=> "4 off")
 * Writing the two halves explicitly high-first fixes the load order but then loses the early
 * pointer setup (mwcc reuses r1 as the load scratch), so the two spellings fail in complementary
 * ways and neither reaches the ROM. build_sweep across all 27 builds reproduces "4 off" on every
 * 2.0/3.0 line; older lines miscompile the size. Same shape as ov236_020d29b8 (scheduling variant);
 * twin ov277_020cfdb8 ties identically. Filed under the reaction-payload-method tie class.
 */

struct Pair16 { unsigned short a, b; };

extern int func_ov107_020c9264(int obj, int a, int b);
extern int func_0203c634(int self, int idx, void *handler);
extern void func_ov244_020cfe90(int self);
extern char data_ov244_020d3724[];

void func_ov244_020cfe20(int self) {
    struct Pair16 local;
    int *node = *(int **)(self + 4);
    void (*method)(int, void *, int);
    func_ov107_020c9264(*node, 1, 0);
    local = *(struct Pair16 *)(data_ov244_020d3724 + 4);
    method = *(void (**)(int, void *, int))(*node + 0x24);
    if (method != 0) {
        method(*node, &local, 4);
    }
    node[7] = 0;
    func_0203c634(self, *(signed char *)(self + 0x20), &func_ov244_020cfe90);
}

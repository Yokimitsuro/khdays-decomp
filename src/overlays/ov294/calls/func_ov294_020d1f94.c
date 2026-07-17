/*
 * Latch the pending sub-state and hand the node's anchor point to the render hook
 * (x3: ov294/295/296).
 *
 * When bit 0 of the hw60 lo byte is set: publish the pending slot (owner+0x1c9 -> +0x1c7), then
 * send the node's anchor -- taken from node_ref[1] with y raised by 0x900 -- to ov107_020c5c54,
 * and advance the indexed slot with no callback.
 *
 * ★ THE CRACK, after 15 ruled-out spellings across three sessions: the block is a VecFx32 and
 * the ROM builds it with the SDK's `VEC_Set` inline, not with a struct copy.
 *
 * The whole gap was one instruction, and every spelling of "copy three words and bump one" gave
 * the same wrong shape:
 *      ROM:   ldm r2,{r2,r3,ip} ; add r3,r3,#0x900 ; str r2,[sp] ; str r3,[sp,#4] ; str ip,[sp,#8]
 *      copy:  ldm+stm, then re-load [sp,#4], add, store it back
 * The ROM groups the three LOADS and does NOT group the stores -- which is SUBOPTIMAL (after the
 * `add` all three words are in registers and an `stm` would have been legal and one instruction
 * cheaper), and that is exactly why no copy spelling reaches it: handed one 3-word destination,
 * mwcc correctly emits the stm.
 *
 * `VEC_Set(&stk, p->x, p->y + 0x900, p->z)` produces both halves for free and for the right
 * reasons: the three ARGUMENTS are three adjacent loads off `p`, which mwcc groups into the ldm;
 * and the inline's body is three separate field stores, which is where the three `str`s come
 * from. There is no copy to optimise, so there is nothing for mwcc to merge.
 *
 * This is the `-inline on,noauto` note in the skill paying off literally: only `inline`-marked
 * functions inline, and the SDK's `static inline` helpers reproduce codegen that open-coding
 * cannot. `VEC_Set` had never been used in a matched file before this one.
 *
 * How it was found: by asking what ov107_020c5c54 does with the block instead of spelling the
 * copy an eleventh way. It passes it to 0203ca30, which writes the three words to +0x10/+0x14/
 * +0x18 and clears a bit at +0x28 -- i.e. it is a 3D vector being stored into a node's transform.
 * Once it is a VecFx32 rather than "three ints", VEC_Set is the obvious way to write it.
 *
 * Last detail: `p` is loaded AFTER the strb. Declared with an initialiser at the top of the
 * block, mwcc hoists the load above the strb and parks it in lr.
 */
struct hw60 { unsigned short lo : 8; unsigned short hi : 8; };
struct Vecx32 { int x, y, z; };

static inline void VEC_Set(struct Vecx32 *vec, int x, int y, int z) {
    vec->x = x;
    vec->y = y;
    vec->z = z;
}

extern void func_ov107_020c5c54(int node, void *blk);
extern int func_0203c634(void *obj, int slot, int arg);

void func_ov294_020d1f94(void *param_1) {
    int *node_ref = *(int **)((char *)param_1 + 4);
    int node = *node_ref;

    if (((struct hw60 *)(node + 0x60))->lo & 1) {
        struct Vecx32 stk;
        struct Vecx32 *p;
        *(signed char *)(node + 0x1c7) = *(signed char *)(node + 0x1c9);
        p = (struct Vecx32 *)node_ref[1];
        VEC_Set(&stk, p->x, p->y + 0x900, p->z);
        func_ov107_020c5c54(*node_ref, &stk);
        func_0203c634(param_1, *(signed char *)((char *)param_1 + 0x20), 0);
    }
}

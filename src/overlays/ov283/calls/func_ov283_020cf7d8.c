typedef unsigned short u16;
typedef struct { int x, y, z; } VecFx32;

extern int func_0203c634(int self, int idx, void *handler);
extern void func_ov283_020cf844(int self);

/* Reaction enter: set pActor+0x388, set hw60 high-byte bit 0, clear node[7], snapshot the target
 * position (VecFx32 at node[1]) into node+0x20, then re-arm the slot with follow-up 020cf844.
 * node=*(ReactionAiNode**)(self+4); *node=pActor. */
void func_ov283_020cf7d8(int self) {
    int *node = *(int **)(self + 4);
    u16 hw;
    *(int *)(*node + 0x388) = 1;
    hw = *(u16 *)(*node + 0x60);
    *(u16 *)(*node + 0x60) = (hw & ~0xff00) |
        ((((((unsigned int)hw << 0x10) >> 0x18) | 1) << 0x18) >> 0x10);
    node[7] = 0;
    *(VecFx32 *)((char *)node + 0x20) = *(VecFx32 *)(node[1]);
    func_0203c634(self, *(signed char *)(self + 0x20), &func_ov283_020cf844);
}

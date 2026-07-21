typedef unsigned short u16;

extern int func_0203c634(int self, int idx, void *handler);

/* Reaction: clear hw60 high-byte bit 0x80, then set its bit 0, re-arm the slot with no handler.
 * hw60 = *(u16*)(*node+0x60), reloaded each op. node=*(ReactionAiNode**)(self+4); *node=pActor. */
void func_ov283_020cf158(int self) {
    int *node = *(int **)(self + 4);
    u16 hw;
    hw = *(u16 *)(*node + 0x60);
    *(u16 *)(*node + 0x60) = (hw & ~0xff00) |
        (((unsigned int)(unsigned short)((((unsigned int)hw << 0x10) >> 0x18) & ~0x80) << 0x18) >> 0x10);
    hw = *(u16 *)(*node + 0x60);
    *(u16 *)(*node + 0x60) = (hw & ~0xff00) |
        ((((((unsigned int)hw << 0x10) >> 0x18) | 1) << 0x18) >> 0x10);
    func_0203c634(self, *(signed char *)(self + 0x20), 0);
}

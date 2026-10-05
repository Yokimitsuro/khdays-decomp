/* c634 state-entry handler: clear obj->f28, run Ov231_AcquireTarget(self), then
 * bias obj->f1c/f18 by +/-0xc91 depending on obj->f49, push the animation frame
 * (obj->f49 + 4) to owner->f388 and owner (Ov107_StartAnim / _020c9264). If
 * obj->f49 >= 2, recompute f1c/f18 from FX_Atan2(obj->f14->f19c, ->f1a4) and
 * push frame 5. Then Ov107_BuildAndSendUpdate(owner, obj->f50, 4, obj->f8), set bit 1 of
 * the owner->f3bc->+8 low byte, and dispatch via SetIndexedSlot. owner re-read per
 * section. self->+0x20 = slot index. */
extern void Ov231_AcquireTarget(int self);
extern void Ov107_StartAnim(int a, int b, int c);
extern void Ov107_PostTagUpdate(int owner, int a, int b);
extern short FX_Atan2(int a, int b);
extern void Ov107_BuildAndSendUpdate(int owner, int a, int b, int c);
extern void SetIndexedSlot(int self, int index, void *cb);
extern void Ov231_AiFollowThenChooseAttack(void);
struct b8 { unsigned int f:8; };
void Ov231_Reaction_BiasFramesAndDispatch(int self) {
    int obj = *(int *)(self + 4);
    int v;
    *(int *)(obj + 0x28) = 0;
    Ov231_AcquireTarget(self);
    v = *(int *)(obj + 0x1c) + (*(unsigned char *)(obj + 0x49) == 0 ? 0xc91 : -0xc91);
    *(int *)(obj + 0x1c) = v;
    *(int *)(obj + 0x18) = v;
    Ov107_StartAnim(*(int *)(*(int *)obj + 0x388), *(unsigned char *)(obj + 0x49) + 4, 0);
    Ov107_PostTagUpdate(*(int *)obj, *(unsigned char *)(obj + 0x49) + 4, 0);
    if (*(unsigned char *)(obj + 0x49) >= 2) {
        v = FX_Atan2(*(int *)(*(int *)(obj + 0x14) + 0x19c), *(int *)(*(int *)(obj + 0x14) + 0x1a4)) + -6434;
        *(int *)(obj + 0x1c) = v;
        *(int *)(obj + 0x18) = v;
        Ov107_StartAnim(*(int *)(*(int *)obj + 0x388), 5, 0);
        Ov107_PostTagUpdate(*(int *)obj, 5, 0);
    }
    Ov107_BuildAndSendUpdate(*(int *)obj, *(short *)(obj + 0x50), 4, *(int *)(obj + 8));
    {
        int tmp = *(int *)(*(int *)obj + 0x3bc);
        ((struct b8 *)(tmp + 8))->f |= 2;
    }
    SetIndexedSlot(self, *(signed char *)(self + 0x20), &Ov231_AiFollowThenChooseAttack);
}

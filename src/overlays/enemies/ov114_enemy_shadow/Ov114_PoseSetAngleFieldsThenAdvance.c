/* Play the anim (ov107 mode 8), compute a value from +0x5c/+0x64 (via FX_Atan2) offset by
 * 0x3244, store it to +0x18/+0x14 and register the handler. */

extern void Ov107_PostTagUpdate();
extern short FX_Atan2();
extern void SetIndexedSlot();
extern void Ov114_AiBrakeUntilGrounded();

void Ov114_PoseSetAngleFieldsThenAdvance(int this_) {
    int node = *(int *)(this_ + 4);
    int a;
    Ov107_PostTagUpdate(*(int *)node, 8, 0);
    a = FX_Atan2(*(int *)(node + 0x5c), *(int *)(node + 0x64)) + 0x3244;
    *(int *)(node + 0x18) = a;
    *(int *)(node + 0x14) = a;
    SetIndexedSlot(this_, *(signed char *)(this_ + 0x20), (int)&Ov114_AiBrakeUntilGrounded);
}

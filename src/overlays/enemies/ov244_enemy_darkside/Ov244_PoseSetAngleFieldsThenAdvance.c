/* Play the anim (ov107 mode 8), compute a value from +0x5c/+0x64 (via 020050b4) offset by
 * 0x3244, store it to +0x18/+0x14 and register the handler. */
extern void Ov107_PostTagUpdate(int a, int b, int c);
extern short FX_Atan2(int a, int b);
extern int SetIndexedSlot(int a, int b, void *handler);
extern void Ov244_AiBrakeUntilGrounded(int);
void Ov244_PoseSetAngleFieldsThenAdvance(int param_1) {
    int child = *(int *)(param_1 + 4);
    int v;
    Ov107_PostTagUpdate(*(int *)child, 8, 0);
    v = FX_Atan2(*(int *)(child + 0x5c), *(int *)(child + 0x64)) + 0x3244;
    *(int *)(child + 0x18) = v;
    *(int *)(child + 0x14) = v;
    SetIndexedSlot(param_1, *(signed char *)(param_1 + 0x20), (void *)&Ov244_AiBrakeUntilGrounded);
}

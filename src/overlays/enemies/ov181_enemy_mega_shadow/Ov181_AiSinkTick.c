/* AI step: flattens the actor into the ground with the timer (its height scale at +0x394, down to a
 * floor of 0xcc); when the
 * timer runs out queues action 0xc and clears the step handler. */

extern int FX_Div(int a, int b);
extern void SetIndexedSlot();

void Ov181_AiSinkTick(int this_) {
    int field0 = *(int *)this_;
    int holder = *(int *)(this_ + 4);
    int t = *(int *)(holder + 0x1c) + *(int *)(field0 + 0x2c);
    *(int *)(holder + 0x1c) = t;
    *(int *)(*(int *)holder + 0x394) = 0x1000 - FX_Div(t, 0x555);
    if (*(int *)(*(int *)holder + 0x394) < 0xcc) {
        *(int *)(*(int *)holder + 0x394) = 0xcc;
    }
    if (*(int *)(holder + 0x1c) < 0x555) return;
    *(signed char *)(*(int *)holder + 0x1c7) = 0xc;
    SetIndexedSlot(this_, *(signed char *)(this_ + 0x20), 0);
}

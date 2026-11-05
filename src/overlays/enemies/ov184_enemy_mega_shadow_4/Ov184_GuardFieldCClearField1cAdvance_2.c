/* AI step: once the gate byte is clear, clears the timer and installs the next step. */

extern void SetIndexedSlot();
extern void Ov184_AiSinkTick();

void Ov184_GuardFieldCClearField1cAdvance_2(int this_) {
    int n = *(int *)(this_ + 4);
    if (*(unsigned char *)*(int *)(n + 0xc)) return;
    *(int *)(n + 0x1c) = 0;
    SetIndexedSlot(this_, *(signed char *)(this_ + 0x20), (int)&Ov184_AiSinkTick);
}

extern void SND_UnlockChannel(unsigned chMask, unsigned lockId);
extern int data_0204a2fc[];

void func_02019d00(unsigned chMask) {
    if (chMask == 0) return;
    SND_UnlockChannel(chMask, 0);
    data_0204a2fc[2] &= ~chMask;
}

extern void SND_LockChannel(unsigned chMask, unsigned lockId);
extern int data_0204a2fc[];

int func_02019cb8(unsigned chMask) {
    if (chMask == 0) return 1;
    if (chMask & (unsigned)data_0204a2fc[2]) return 0;
    SND_LockChannel(chMask, 0);
    data_0204a2fc[2] |= chMask;
    return 1;
}

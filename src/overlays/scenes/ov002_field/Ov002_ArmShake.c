extern char *data_ov002_0207f628;

extern unsigned long long OS_GetTick(void);
extern void Tween_Clear(char *pEmitter);

/* Arm the shake for the given duration: record it with the current tick, raise
 * the two active flags, and pick the profile. Short shakes take the simple
 * path; long ones clear it and restart the emitter. */
void Ov002_ArmShake(unsigned long long nTicks)
{
    unsigned int nDuration = (unsigned int)nTicks;
    char *pOwner;

    pOwner = data_ov002_0207f628;
    if (pOwner == 0) {
        return;
    }

    *(unsigned int *)(pOwner + 0x1064) = nDuration;
    *(unsigned long long *)(pOwner + 0x105c) = OS_GetTick();

    *(int *)(pOwner + 0xcc) = 1;
    *(int *)(pOwner + 0xfec) = 1;

    if (nDuration < 0xbb8) {
        *(int *)(pOwner + 0xd4) = 1;
        return;
    }

    *(int *)(pOwner + 0xd4) = 0;
    Tween_Clear(pOwner + 0xfd0);
}

extern char *data_ov002_0207f628;

extern unsigned long long func_020031d4(void);
extern void func_02035f84(char *pEmitter);

/* Arm the shake for the given duration: record it with the current tick, raise
 * the two active flags, and pick the profile. Short shakes take the simple
 * path; long ones clear it and restart the emitter. */
void func_ov002_02061ab0(unsigned int nDuration)
{
    char *pOwner;

    pOwner = data_ov002_0207f628;
    if (pOwner == 0) {
        return;
    }

    *(unsigned int *)(pOwner + 0x1064) = nDuration;
    *(unsigned long long *)(pOwner + 0x105c) = func_020031d4();

    *(int *)(pOwner + 0xcc) = 1;
    *(int *)(pOwner + 0xfec) = 1;

    if (nDuration < 0xbb8) {
        *(int *)(pOwner + 0xd4) = 1;
        return;
    }

    *(int *)(pOwner + 0xd4) = 0;
    func_02035f84(pOwner + 0xfd0);
}

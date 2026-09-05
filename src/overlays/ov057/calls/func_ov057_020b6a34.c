/* Re-arms the five tracks of a swing sequence for the given phase: sets the
 * sequence state, releases every previous handle, binds each track to the
 * requested source/phase, and restarts its frame from zero. The
 * actor is not touched -- the caller passes it only because every routine in
 * the family takes it first. */
typedef unsigned short u16;

extern void func_02014dc4(void *p, int handle);
extern void func_0202accc(void *p, u16 idx, int a, short b);
extern void func_01fff774(void *p, u16 idx, int a);

void func_ov057_020b6a34(int pActor, int *pSwing, int phase)
{
    int trackIndex;

    switch (phase) {
    case 0:
        pSwing[0] = 1;
        break;
    case 1:
        pSwing[0] = 3;
        break;
    case 2:
        pSwing[0] = 2;
        break;
    case 3:
        pSwing[0] = 3;
        break;
    }
    for (trackIndex = 0; trackIndex < 5; trackIndex++) {
        if (pSwing[trackIndex + 4] != 0) {
            func_02014dc4((char *)pSwing + 0x24, pSwing[trackIndex + 4]);
            pSwing[trackIndex + 4] = 0;
        }
        func_0202accc((char *)pSwing + 4, (u16)trackIndex,
                      *(int *)((char *)pSwing + 0x10c), (short)phase);
        func_01fff774((char *)pSwing + 4, (u16)trackIndex, 0);
    }
}

/*
 * Ov002_TryAdvancePhase - gameplay-state handler returned by Ov002_TickGameplayState (and by
 * Ov002_RunPendingCallbacks). Gates on a series of readiness checks and, when they pass, hands
 * off to func_ov002_02068e34.
 *
 * Returns NULL while the global busy byte data_0204be04 is set, if the optional gate callback at
 * heap+0x8b90 reports not-ready (returns 0), or if func_ov002_0206f59c / func_ov002_020693e0
 * report not-ready. Otherwise: unless the phase tag at heap+0x8baa is -3 with the session
 * inactive (func_02030670), it re-enables the lazy class (Ov002_SetLazyClassEnabled(1)); then it
 * returns func_ov002_02068e34.
 *
 * THUMB. The heap base is NNSi_FndGetCurrentRootHeap(). The return handler is latched before the
 * final check (so it survives the session/lazy-class calls in r4); declaring it ahead of the
 * base is what lands it in r4 and the base in r5, matching the original allocation.
 */

typedef unsigned char u8;
typedef int (*Fn)(void);

extern int  NNSi_FndGetCurrentRootHeap(void);
extern int  func_ov002_0206f59c(void);
extern int  func_ov002_020693e0(void);
extern int  func_02030670(void);
extern void func_ov002_0206e718(int a);
extern void func_ov002_02068e34(void);
extern u8   data_0204be04;

void *func_ov002_02068dc4(void)
{
    void *result;
    int base = NNSi_FndGetCurrentRootHeap();
    Fn cb;

    if (data_0204be04 != 0) return 0;
    cb = *(Fn *)(base + 0x8b90);
    if (cb != 0 && cb() == 0) return 0;
    if (func_ov002_0206f59c() == 0) return 0;
    if (func_ov002_020693e0() == 0) return 0;
    result = (void *)func_ov002_02068e34;
    if (*(short *)(base + 0x8baa) != -3 || func_02030670() != 0) {
        func_ov002_0206e718(1);
    }
    return result;
}

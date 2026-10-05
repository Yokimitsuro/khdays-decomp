/* Ov000_HoldTimerState -- Scene 1 (boot/logo) hold-timer state, ov000.
 * On first entry (heap[0x4c5c] flag set) it latches a target time
 * ((tick*64)/0x82ea + 0x7d0) into heap[0x4c60], clears the flag, and if
 * Ov000_BackupAccessGate() reports "skip" it jumps straight to Ov000_ShowErrorAndHalt
 * (marking boot sub-mode heap[0x1313]=2). Otherwise it waits: each frame it
 * recomputes the scaled tick and, once it reaches the target, wipes the scene
 * heap (0x507c bytes) and restarts the graphics setup via Ov000_FreshBootGfxSetup;
 * until then it returns 0 (stay). */

typedef void *StateFn;

extern void *NNSi_FndGetCurrentRootHeap(void);
extern void  Ov000_SetupBootTextScreen(int);
extern unsigned long long OS_GetTick(void);
extern unsigned long long func_02020368(unsigned long long dividend, unsigned long long divisor);
extern int   Ov000_BackupAccessGate(void);
extern void  MI_CpuFill8(void *dst, int val, int size);
extern StateFn Ov000_FreshBootGfxSetup(int arg);
extern void  Ov000_ShowErrorAndHalt(void);

StateFn Ov000_HoldTimerState(void) {
    char *h = (char *)NNSi_FndGetCurrentRootHeap();
    if (*(int *)(h + 0x4c5c) != 0) {
        Ov000_SetupBootTextScreen(0);
        *(unsigned int *)(h + 0x4c60) =
            (unsigned int)(func_02020368(OS_GetTick() << 6, 0x82ea) + 0x7d0);
        *(int *)(h + 0x4c5c) = 0;
        if (Ov000_BackupAccessGate() == 0) {
            *(int *)(h + 0x4c4c) = 2;
            return (StateFn)Ov000_ShowErrorAndHalt;
        }
    }
    if (func_02020368(OS_GetTick() << 6, 0x82ea) < *(unsigned int *)(h + 0x4c60)) {
        return 0;
    }
    MI_CpuFill8(h, 0, 0x507c);
    return Ov000_FreshBootGfxSetup(0);
}

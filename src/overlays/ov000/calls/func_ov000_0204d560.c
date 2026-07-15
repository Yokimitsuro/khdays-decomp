/* func_ov000_0204d560 -- Scene 1 (boot/logo) hold-timer state, ov000.
 * On first entry (heap[0x4c5c] flag set) it latches a target time
 * ((tick*64)/0x82ea + 0x7d0) into heap[0x4c60], clears the flag, and if
 * func_ov000_02054c20() reports "skip" it jumps straight to func_ov000_0204f6c8
 * (marking boot sub-mode heap[0x1313]=2). Otherwise it waits: each frame it
 * recomputes the scaled tick and, once it reaches the target, wipes the scene
 * heap (0x507c bytes) and restarts the graphics setup via func_ov000_0204d7c8;
 * until then it returns 0 (stay). */

typedef void *StateFn;

extern void *NNSi_FndGetCurrentRootHeap(void);
extern void  func_ov000_0204d358(int);
extern unsigned long long func_020031d4(void);
extern unsigned long long func_02020368(unsigned long long value, unsigned int divisor, int arg3);
extern int   func_ov000_02054c20(void);
extern void  MI_CpuFill8(void *dst, int val, int size);
extern StateFn func_ov000_0204d7c8(int arg);
extern void  func_ov000_0204f6c8(void);

StateFn func_ov000_0204d560(void) {
    char *h = (char *)NNSi_FndGetCurrentRootHeap();
    if (*(int *)(h + 0x4c5c) != 0) {
        func_ov000_0204d358(0);
        *(unsigned int *)(h + 0x4c60) =
            (unsigned int)(func_02020368(func_020031d4() << 6, 0x82ea, 0) + 0x7d0);
        *(int *)(h + 0x4c5c) = 0;
        if (func_ov000_02054c20() == 0) {
            *(int *)(h + 0x4c4c) = 2;
            return (StateFn)func_ov000_0204f6c8;
        }
    }
    if (func_02020368(func_020031d4() << 6, 0x82ea, 0) < *(unsigned int *)(h + 0x4c60)) {
        return 0;
    }
    MI_CpuFill8(h, 0, 0x507c);
    return func_ov000_0204d7c8(0);
}

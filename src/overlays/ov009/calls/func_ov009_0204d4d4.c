/*
 * func_ov009_0204d4d4 -- x3 (ov008/...). Allocate the screen's work buffer and object, then advance.
 * Context at data_02090f04[1]+0x9000. Notify the owned object (020513f0 on +0x59c). If the work buffer
 * +0x95a0 is unallocated: prime it via 02051424(+0x95c8), query its size (02051b00), allocate from the
 * default expheap and zero it. If the object handle +0x9624 is unset, create it via 02051458(buffer).
 * Bail if the object still could not be made; otherwise advance to phase 6 (0204ee28) and blit the
 * config region (0204eff0(0, 100)).
 *
 * The `volatile` context reads (CTXV) at the memset destination, the +0x9624 store and the final
 * +0x9624 test are matching devices: the retail compiler re-loads data_02090f04[1] there, but mwcc
 * 3.0/139 reuses the just-stored value / a precomputed address. The volatile forces the reload;
 * behaviour is identical.
 */
extern void func_ov009_0204e750(int obj);
extern void func_ov009_0204e784(int a);
extern int func_ov009_0204ee30(void);
extern void *NNSi_FndAllocFromDefaultExpHeap(unsigned size);
extern void MI_CpuFill8(void *dst, int val, unsigned size);
extern int func_ov009_0204e7b8(int buffer);
extern void func_ov009_0204cb6c(int phase);
extern void func_ov009_0204cd34(int a, int b);
extern int data_ov009_020563e4[];

#define CTX  (data_ov009_020563e4[1])
#define CTXV (*(volatile int *)((char *)data_ov009_020563e4 + 4))

void func_ov009_0204d4d4(void) {
    func_ov009_0204e750(*(int *)(CTX + 0x959c));
    if (*(int *)(CTX + 0x95a0) == 0) {
        unsigned size;
        func_ov009_0204e784(*(int *)(CTX + 0x95c8));
        size = func_ov009_0204ee30();
        *(void **)(CTX + 0x95a0) = NNSi_FndAllocFromDefaultExpHeap(size);
        MI_CpuFill8(*(void **)(CTXV + 0x95a0), 0, size);
    }
    if (*(int *)(CTX + 0x9624) == 0) {
        *(int *)(CTXV + 0x9624) = func_ov009_0204e7b8(*(int *)(CTX + 0x95a0));
    }
    if (*(int *)(CTXV + 0x9624) == 0) {
        return;
    }
    func_ov009_0204cb6c(6);
    func_ov009_0204cd34(0, 100);
}

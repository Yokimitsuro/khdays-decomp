/*
 * func_ov025_02083758 -- x3 (ov008/...). Allocate the screen's work buffer and object, then advance.
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
extern void func_ov025_020851a0(int obj);
extern void func_ov025_020851d4(int a);
extern int func_ov025_020858b0(void);
extern void *NNSi_FndAllocFromDefaultExpHeap(unsigned size);
extern void MI_CpuFill8(void *dst, int val, unsigned size);
extern int func_ov025_02085208(int buffer);
extern void func_ov025_02082c50(int phase);
extern void func_ov025_02082e18(int a, int b);
extern int data_ov025_020b5744[];

#define CTX  (data_ov025_020b5744[1])
#define CTXV (*(volatile int *)((char *)data_ov025_020b5744 + 4))

void func_ov025_02083758(void) {
    func_ov025_020851a0(*(int *)(CTX + 0x959c));
    if (*(int *)(CTX + 0x95a0) == 0) {
        unsigned size;
        func_ov025_020851d4(*(int *)(CTX + 0x95c8));
        size = func_ov025_020858b0();
        *(void **)(CTX + 0x95a0) = NNSi_FndAllocFromDefaultExpHeap(size);
        MI_CpuFill8(*(void **)(CTXV + 0x95a0), 0, size);
    }
    if (*(int *)(CTX + 0x9624) == 0) {
        *(int *)(CTXV + 0x9624) = func_ov025_02085208(*(int *)(CTX + 0x95a0));
    }
    if (*(int *)(CTXV + 0x9624) == 0) {
        return;
    }
    func_ov025_02082c50(6);
    func_ov025_02082e18(0, 100);
}

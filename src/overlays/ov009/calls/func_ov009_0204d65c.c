/*
 * func_ov009_0204d65c -- x3 (ov008/...). Full sub-screen teardown, then branch on the pending id.
 * Context at data_02090f04[1]+0x9000. Destroy all registry entries (02050dd0). If the work object
 * +0x95f8 is present: notify +0x95a0 (02051498), free it if allocated and null it, clear +0x9624, run
 * shared teardown 0204ef90 + 02051438. Always finalise the font buffer: 020513bc(+0x59c), free +0x59c
 * if allocated and null it, clear +0x9620, run 0204ef30 + 0205135c. If the pending id +0x95c4 is -1,
 * reset to phase 0 and finalise (02050b20); otherwise go to phase 1.
 */
extern void func_ov009_0204e540(void);
extern void func_ov009_0204e7f8(int obj);
extern void NNSi_FndFreeFromDefaultHeap(int obj);
extern void func_ov009_0204ccd4(void);
extern void func_ov009_0204e798(void);
extern void func_ov009_0204e71c(int obj);
extern void func_ov009_0204cc74(void);
extern void func_ov009_0204e6bc(void);
extern void func_ov009_0204cb6c(int phase);
extern void func_ov009_0204e3d8(void);
extern int data_ov009_020563e4[];

#define CTX  (data_ov009_020563e4[1])
#define CTXV (*(volatile int *)((char *)data_ov009_020563e4 + 4))

void func_ov009_0204d65c(void) {
    int p;

    func_ov009_0204e540();
    if (*(int *)(CTX + 0x95f8) != 0) {
        func_ov009_0204e7f8(*(int *)(CTX + 0x95a0));
        p = *(int *)(CTX + 0x95a0);
        if (p != 0) {
            NNSi_FndFreeFromDefaultHeap(p);
            *(int *)(CTXV + 0x95a0) = 0;
        }
        *(int *)(CTXV + 0x9624) = 0;
        func_ov009_0204ccd4();
        func_ov009_0204e798();
    }
    func_ov009_0204e71c(*(int *)(CTX + 0x959c));
    p = *(int *)(CTX + 0x959c);
    if (p != 0) {
        NNSi_FndFreeFromDefaultHeap(p);
        *(int *)(CTXV + 0x959c) = 0;
    }
    *(int *)(CTXV + 0x9620) = 0;
    func_ov009_0204cc74();
    func_ov009_0204e6bc();
    if (*(int *)(CTX + 0x95c4) == -1) {
        func_ov009_0204cb6c(0);
        func_ov009_0204e3d8();
        return;
    }
    func_ov009_0204cb6c(1);
}

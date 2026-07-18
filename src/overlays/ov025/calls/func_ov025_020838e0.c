/*
 * func_ov025_020838e0 -- x3 (ov008/...). Full sub-screen teardown, then branch on the pending id.
 * Context at data_02090f04[1]+0x9000. Destroy all registry entries (02050dd0). If the work object
 * +0x95f8 is present: notify +0x95a0 (02051498), free it if allocated and null it, clear +0x9624, run
 * shared teardown 0204ef90 + 02051438. Always finalise the font buffer: 020513bc(+0x59c), free +0x59c
 * if allocated and null it, clear +0x9620, run 0204ef30 + 0205135c. If the pending id +0x95c4 is -1,
 * reset to phase 0 and finalise (02050b20); otherwise go to phase 1.
 */
extern void func_ov025_02084bf8(void);
extern void func_ov025_02085248(int obj);
extern void NNSi_FndFreeFromDefaultHeap(int obj);
extern void func_ov025_02082db8(void);
extern void func_ov025_020851e8(void);
extern void func_ov025_0208516c(int obj);
extern void func_ov025_02082d58(void);
extern void func_ov025_0208510c(void);
extern void func_ov025_02082c50(int phase);
extern void func_ov025_02084948(void);
extern int data_ov025_020b5744[];

#define CTX  (data_ov025_020b5744[1])
#define CTXV (*(volatile int *)((char *)data_ov025_020b5744 + 4))

void func_ov025_020838e0(void) {
    int p;

    func_ov025_02084bf8();
    if (*(int *)(CTX + 0x95f8) != 0) {
        func_ov025_02085248(*(int *)(CTX + 0x95a0));
        p = *(int *)(CTX + 0x95a0);
        if (p != 0) {
            NNSi_FndFreeFromDefaultHeap(p);
            *(int *)(CTXV + 0x95a0) = 0;
        }
        *(int *)(CTXV + 0x9624) = 0;
        func_ov025_02082db8();
        func_ov025_020851e8();
    }
    func_ov025_0208516c(*(int *)(CTX + 0x959c));
    p = *(int *)(CTX + 0x959c);
    if (p != 0) {
        NNSi_FndFreeFromDefaultHeap(p);
        *(int *)(CTXV + 0x959c) = 0;
    }
    *(int *)(CTXV + 0x9620) = 0;
    func_ov025_02082d58();
    func_ov025_0208510c();
    if (*(int *)(CTX + 0x95c4) == -1) {
        func_ov025_02082c50(0);
        func_ov025_02084948();
        return;
    }
    func_ov025_02082c50(1);
}

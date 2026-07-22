/* Scene entry gate: refuse (reporting no step) while data_0204be04 is set, and
 * again if func_ov002_02069454 finds nothing to show. Only then close the
 * pending dialog and run the setup, handing back the step at
 * func_ov002_02068e68. NNSi_FndGetCurrentRootHeap is called for its side effect
 * only -- the ROM discards r0. */
extern void *NNSi_FndGetCurrentRootHeap(void);
extern int func_ov002_02069454(void);
extern void func_02023c30(int a);
extern void func_ov002_020692a8(void);
extern void func_ov002_02068e68(void);

extern unsigned char data_0204be04;

void *func_ov002_02068e34(void) {
    NNSi_FndGetCurrentRootHeap();

    if (data_0204be04 != 0) {
        return 0;
    }
    if (func_ov002_02069454() == 0) {
        return 0;
    }

    func_02023c30(0);
    func_ov002_020692a8();
    return (void *)&func_ov002_02068e68;
}

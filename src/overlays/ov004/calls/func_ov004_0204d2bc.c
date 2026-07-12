/* Tear down the manager: run the two release passes, then free the element buffer at
 * +0x14 if it is still allocated. */
extern void func_ov004_0204cae8(int a);
extern void func_ov004_0204d148(int a);
extern void NNSi_FndFreeFromDefaultHeap(int a);
void func_ov004_0204d2bc(int param_1) {
    func_ov004_0204cae8(param_1);
    func_ov004_0204d148(param_1);
    if (*(int *)(param_1 + 0x14) == 0) return;
    NNSi_FndFreeFromDefaultHeap(*(int *)(param_1 + 0x14));
    *(int *)(param_1 + 0x14) = 0;
}

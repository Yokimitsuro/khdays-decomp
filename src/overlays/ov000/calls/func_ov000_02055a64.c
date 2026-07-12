/* Build the transient blob, hand it to 02055a24, then free it. */
extern int func_0201ef9c(int data, int kind);
extern void func_ov000_02055a24(int self, int obj, int arg);
extern void NNSi_FndFreeFromDefaultHeap(void *obj);
void func_ov000_02055a64(int param_1, int param_2, int param_3) {
    int obj = func_0201ef9c(param_2, 0xe);
    func_ov000_02055a24(param_1, obj, param_3);
    if (obj != 0) NNSi_FndFreeFromDefaultHeap((void *)obj);
}

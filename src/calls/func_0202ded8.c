/* Release the pending deferred-draw handle (data_0204c20c[1]) if any: run its
 * finalizer (func_020163f4 with the supplied args), free the buffer, and clear both
 * slots of the handle pair. Returns 1. */
#pragma thumb on
extern void func_020163f4(unsigned int *h, int b, int c, int d);
extern void NNSi_FndFreeFromDefaultHeap(void *p);
extern int data_0204c20c[];
int func_0202ded8(int param_1, int param_2, int param_3, int param_4) {
    if ((unsigned int *)data_0204c20c[1] != 0) {
        func_020163f4((unsigned int *)data_0204c20c[1], param_2, param_3, param_4);
        NNSi_FndFreeFromDefaultHeap((void *)data_0204c20c[1]);
        data_0204c20c[1] = 0;
        data_0204c20c[0] = 0;
    }
    return 1;
}

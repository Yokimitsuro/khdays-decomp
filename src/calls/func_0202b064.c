/* Tear down an object's sub-resource table: for each of the param_1[1] entries in the
 * array at param_1[+4] free the non-null slot (func_02028d70) and null it, then free the
 * array itself (NNSi_FndFreeFromDefaultHeap) and clear the count/array-pointer header. */
#pragma thumb on
extern void func_02028d70(void);
extern void NNSi_FndFreeFromDefaultHeap(void *p);
void func_0202b064(unsigned short *param_1) {
    int i = 0;
    if (i < (int)(unsigned short)param_1[1]) {
        int off = 0;
        do {
            if (*(int *)(*(int *)(param_1 + 2) + off) != 0) {
                func_02028d70();
                *(int *)(*(int *)(param_1 + 2) + off) = 0;
            }
            i++;
            off += 4;
        } while (i < (int)(unsigned short)param_1[1]);
    }
    if (*(int *)(param_1 + 2) != 0) {
        NNSi_FndFreeFromDefaultHeap((void *)*(int *)(param_1 + 2));
        *(int *)(param_1 + 2) = 0;
    }
    param_1[1] = 0;
    param_1[0] = 0;
}

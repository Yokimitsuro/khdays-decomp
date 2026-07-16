/* func_ov008_0205c968 -- free the five scratch buffers of an ov008 object (obj+0x207c..0x208c). */
extern void NNSi_FndFreeFromDefaultHeap(void *p);

void func_ov008_0205c968(int param_1) {
    NNSi_FndFreeFromDefaultHeap(*(void **)(param_1 + 0x208c));
    NNSi_FndFreeFromDefaultHeap(*(void **)(param_1 + 0x2088));
    NNSi_FndFreeFromDefaultHeap(*(void **)(param_1 + 0x2084));
    NNSi_FndFreeFromDefaultHeap(*(void **)(param_1 + 0x2080));
    NNSi_FndFreeFromDefaultHeap(*(void **)(param_1 + 0x207c));
}

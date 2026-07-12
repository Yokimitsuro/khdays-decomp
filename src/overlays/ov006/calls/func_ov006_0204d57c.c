/* Twin of func_ov026_02084d64: free the buffer held at *param_1 (if any). */
extern void NNSi_FndFreeFromDefaultHeap(void *ptr);
void func_ov006_0204d57c(void **param_1) {
    if (*param_1 != 0) {
        NNSi_FndFreeFromDefaultHeap(*param_1);
    }
}

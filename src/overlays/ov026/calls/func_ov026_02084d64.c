/* Free the buffer held at *param_1 (if any) back to the default heap. */
extern void NNSi_FndFreeFromDefaultHeap(void *ptr);
void func_ov026_02084d64(void **param_1) {
    if (*param_1 != 0) {
        NNSi_FndFreeFromDefaultHeap(*param_1);
    }
}

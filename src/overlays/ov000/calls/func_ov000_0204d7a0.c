/* func_ov000_0204d7a0 -- release the logo scene resources, ov000. Releases the base
 * resource (heap[1]) and, when present, the region resource (heap[2]) via func_02024fd4. */
extern void *NNSi_FndGetCurrentRootHeap(void);
extern void func_02024fd4(void *res);
void func_ov000_0204d7a0(void) {
    int *h = (int *)NNSi_FndGetCurrentRootHeap();
    func_02024fd4((void *)h[1]);
    if (h[2] != 0) {
        func_02024fd4((void *)h[2]);
    }
}

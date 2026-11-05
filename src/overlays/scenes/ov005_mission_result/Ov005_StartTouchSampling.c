/* Ov005_StartTouchSampling -- spawn the ov005 worker task, ov005 (tail-call to TP_RequestAutoSamplingStartAsync
 * with priority 4, stack idx 5, on the boot arena gMainHeap). */
extern int TP_RequestAutoSamplingStartAsync(int a, int prio, void *arena, int stackIdx);
extern int gMainHeap;
int Ov005_StartTouchSampling(void) {
    return TP_RequestAutoSamplingStartAsync(0, 4, &gMainHeap, 5);
}

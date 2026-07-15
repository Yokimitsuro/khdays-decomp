/* func_ov000_0204d208 -- register the 10 logo objects with the sub-object manager,
 * ov000. Re-adds each object (heap[0x1301+i]) to the manager @heap[0x6c] via
 * func_020324ac, then commits with func_0203253c. */
extern void *NNSi_FndGetCurrentRootHeap(void);
extern void func_020324ac(void *mgr, void *obj);
extern void func_0203253c(void *mgr);
void func_ov000_0204d208(void) {
    int *h = (int *)NNSi_FndGetCurrentRootHeap();
    int i;
    for (i = 0; i < 10; i++) {
        func_020324ac((void *)(h + 0x6c), ((void **)h)[0x1301 + i]);
    }
    func_0203253c((void *)(h + 0x6c));
}

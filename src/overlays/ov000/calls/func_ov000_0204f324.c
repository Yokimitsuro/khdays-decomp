extern char *NNSi_FndGetCurrentRootHeap(void);
extern int func_ov000_0205a4bc(void);
extern void WM_EndKeySharing_0x02023ad0(int h);
extern void func_0201e1d0(void);
extern int func_ov000_0204d7c8(int a);
extern int data_ov000_0205ac20;

/* Once the movie player reaches state 6, releases its handle and hands control back to the
 * title. Returns 1 when it acted, 0 while the movie is still running. */
int func_ov000_0204f324(void) {
    char *heap = NNSi_FndGetCurrentRootHeap();
    if (func_ov000_0205a4bc() != 6) {
        return 0;
    }
    WM_EndKeySharing_0x02023ad0(*(int *)(heap + 0x5000 + 0x74));
    data_ov000_0205ac20 = 0;
    func_0201e1d0();
    return func_ov000_0204d7c8(1);
}

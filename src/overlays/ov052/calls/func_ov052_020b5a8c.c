extern char *NNSi_FndGetCurrentRootHeap(void);
extern void func_ov052_020b6e18(void);
extern void func_ov052_020b71f8(char *heap);
extern void WM_EndKeySharing_0x02023ad0(int h);
extern void func_0202a7dc(char *p);
extern void func_0202a440(char *p);
extern void func_ov022_0209fab4(char *heap);

/* Enemy overlay teardown: drops the model handle, the two animation blocks and the sound block,
 * then hands the heap back to the shared unloader. */
void func_ov052_020b5a8c(void) {
    char *heap = NNSi_FndGetCurrentRootHeap();
    func_ov052_020b6e18();
    func_ov052_020b71f8(heap);
    WM_EndKeySharing_0x02023ad0(*(int *)(heap + 0x2c2c));
    func_0202a7dc(heap + 0x2c34);
    func_0202a7dc(heap + 0x2d3c);
    func_0202a440(heap + 0x2e44);
    func_ov022_0209fab4(heap);
}

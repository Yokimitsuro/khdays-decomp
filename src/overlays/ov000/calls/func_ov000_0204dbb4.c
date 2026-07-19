extern char *NNSi_FndGetCurrentRootHeap(void);
extern void func_0200c5fc(void);
extern void func_0200ca50(int a);
extern void func_0200ca68(int a);
extern void func_02032428(char *p);
extern void func_020362e8(char *p);
extern void NNSi_FndFreeFromDefaultHeap(void *p);
extern void func_0202a7dc(char *p);
extern int func_02024e5c(void);
extern void func_020235e8(int id, int a, unsigned short b);
extern int data_ov000_0205ac20;

/* Title teardown: stops the two sound channels, releases the layout and the animation block
 * (unless the "keep" flag is set), frees the scratch buffer and reports the exit reason. */
void func_ov000_0204dbb4(void) {
    char *heap = NNSi_FndGetCurrentRootHeap();
    func_0200c5fc();
    func_0200ca50(4);
    func_0200ca68(4);
    if (*(int *)(heap + 0x4000 + 0xc40) == 0) {
        func_02032428(heap + 0x1b0);
    }
    func_020362e8(heap + 0x3e8 + 0x4800);
    NNSi_FndFreeFromDefaultHeap(*(void **)(heap + 0x14c));
    func_0202a7dc(heap + 0xc);
    func_020235e8(0x2011, 3, (unsigned short)func_02024e5c());
    data_ov000_0205ac20 = 0;
}

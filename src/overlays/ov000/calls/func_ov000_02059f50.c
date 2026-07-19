extern void *NNSi_FndGetCurrentRootHeap(void);
extern void NNSi_FndFreeFromDefaultHeap(void *p);
extern void func_ov000_02056960(char *p);
extern void func_0202ffbc(char *p);
extern void func_0202ff7c(char *p);
extern void func_ov000_020568c8(char *p);
extern void func_ov000_0205651c(char *p);
extern void func_ov000_02055ad8(char *p);
extern void func_ov000_02055b0c(char *p);
extern void func_0200c5fc(void);
extern void func_0200ca50(int a);
extern void func_0200ca68(int a);
extern void func_020362e8(char *p);
extern void G3X_SetHOffset(int off);
extern int data_ov000_0205ac3c;

/* Title/menu teardown: frees the scratch buffer, releases every sub-allocator and the two
 * layout blocks, stops the two sound channels and resets the 3D horizontal offset. */
void func_ov000_02059f50(void) {
    char *heap = (char *)NNSi_FndGetCurrentRootHeap();
    if (*(void **)(heap + 0xd000 + 0x110) != 0) {
        NNSi_FndFreeFromDefaultHeap(*(void **)(heap + 0xd000 + 0x110));
        *(void **)(heap + 0xd000 + 0x110) = 0;
    }
    func_ov000_02056960(heap + 0x88);
    func_0202ffbc(heap + 0x94);
    func_0202ffbc(heap + 0xd0);
    func_0202ff7c(heap + 0x258 + 0x9400);
    func_ov000_020568c8(heap + 0x10c);
    func_ov000_0205651c(heap + 0x10c);
    func_ov000_02055ad8(heap + 0x158);
    func_ov000_02055ad8(heap + 0x3d8 + 0x4800);
    func_ov000_02055b0c(heap + 0x158);
    func_ov000_02055b0c(heap + 0x3d8 + 0x4800);
    func_0200c5fc();
    func_0200ca50(4);
    func_0200ca68(4);
    func_020362e8(heap + 0x68);
    G3X_SetHOffset(0);
    data_ov000_0205ac3c = 0;
}

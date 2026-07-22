/* Scene entry: the context IS the current root heap block (nothing is allocated),
 * so latch it in data_ov002_0207f9f4 and zero its first 0x25 bytes, then register
 * the per-frame step at func_ov002_02066cc8 under slot 6. Returns the next scene
 * step. Same shape as func_ov002_02062bd8. */
extern void *NNSi_FndGetCurrentRootHeap(void);
extern void MI_CpuFill8(void *dst, unsigned char value, unsigned int size);
extern void func_02030cf8(int slot, void *fn);
extern void func_ov002_02066cc8(void);
extern void func_ov002_02066d78(void);

extern int data_ov002_0207f9f4;

void *func_ov002_02066d38(void) {
    void *ctx = NNSi_FndGetCurrentRootHeap();

    data_ov002_0207f9f4 = (int)ctx;
    MI_CpuFill8(ctx, 0, 0x25);
    func_02030cf8(6, (void *)&func_ov002_02066cc8);
    return (void *)&func_ov002_02066d78;
}

extern char *NNSi_FndGetCurrentRootHeap(void);
extern void MI_CpuFill8(void *dst, int value, unsigned size);
extern void *NNS_FndAllocFromDefaultExpHeapEx(unsigned size, int align);
extern void MIi_CpuClearFast(int value, void *dst, unsigned size);
extern void func_ov002_02052a6c(void *desc, void *handler, int arg);
extern void func_ov002_02064cc0(void);
extern int func_ov002_02063580(void);
extern void func_ov002_02065698(void);
extern int func_ov002_020538c0(void *fn);
extern void func_ov002_02064bf0(void);
extern void func_ov002_02064c1c(void);
extern void func_ov002_02065638(void);
extern char *data_ov002_0207f638;
extern int data_ov002_0207ee54;

/* Sets up the save/load page: clears the scene block, allocates and clears the 0x12c0-byte entry
 * table, builds the button, and registers the row renderer; returns the page's tick handler. */
void *func_ov002_0206558c(void) {
    char *self = NNSi_FndGetCurrentRootHeap();
    data_ov002_0207f638 = self;
    MI_CpuFill8(self, 0, 0x44);
    *(void **)(self + 0x1c) = NNS_FndAllocFromDefaultExpHeapEx(0x4b << 6, 4);
    MIi_CpuClearFast(0, *(void **)(self + 0x1c), 0x4b << 6);
    func_ov002_02052a6c(&data_ov002_0207ee54, (void *)&func_ov002_02064bf0, 0);
    func_ov002_02064cc0();
    if (func_ov002_02063580() != 0xffff) {
        func_ov002_02065698();
    }
    *(int *)(self + 0x34) = func_ov002_020538c0((void *)&func_ov002_02064c1c);
    return (void *)&func_ov002_02065638;
}

extern char *NNSi_FndGetCurrentRootHeap(void);
extern void func_02030cf8(int slot, void *handler);
extern void MI_CpuFill8(void *dst, int value, unsigned size);
extern void func_ov022_0208a1a4(void);
extern int func_02030788(void);
extern void func_ov022_0208973c(void);
extern void func_ov022_020897dc(void);
extern void func_ov022_02089784(void);
extern void func_ov022_02089d90(void);
extern void func_ov022_02089704(void);
extern char *data_ov022_020b2ea4;

/* Sets the pause menu up: registers its four input handlers, clears the state block and -- on
 * the single-card path -- invalidates the four peer slots. Returns the tick handler. */
void *func_ov022_02089654(void) {
    char *self = NNSi_FndGetCurrentRootHeap();
    int i;
    data_ov022_020b2ea4 = self;
    *(int *)self = 0;
    func_02030cf8(2, (void *)&func_ov022_0208973c);
    func_02030cf8(0, (void *)&func_ov022_020897dc);
    func_02030cf8(3, (void *)&func_ov022_02089784);
    func_02030cf8(0xf, (void *)&func_ov022_02089d90);
    MI_CpuFill8(self + 0x14, 0, 0xa4);
    MI_CpuFill8(self + 0x14, 0, 0xc4);
    func_ov022_0208a1a4();
    if (func_02030788() == 0) {
        for (i = 0; i < 4; i++) {
            *(unsigned short *)(self + 0xb0) = 0xffff;
            self += 2;
        }
    }
    return (void *)&func_ov022_02089704;
}

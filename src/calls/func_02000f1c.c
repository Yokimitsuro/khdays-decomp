extern void MI_CpuFill8(void *dst, unsigned char val, unsigned int size);
extern void OS_SetIrqFunction(int mask, void (*cb)(void));
extern int OS_EnableIrqMask(int mask);
extern void GX_VBlankIntr(int enable);

extern char data_027e0088[];
extern void func_01ff8000(void);

void func_02000f1c(void) {
    MI_CpuFill8(data_027e0088, 0, 0x88);
    OS_SetIrqFunction(1, func_01ff8000);
    OS_EnableIrqMask(1);
    GX_VBlankIntr(1);
}

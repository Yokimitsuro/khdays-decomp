extern char *func_ov002_020636ac(void);
extern char *NNSi_FndGetCurrentRootHeap(void);
extern void MI_CpuFill8(void *dst, int value, unsigned size);
extern void func_ov002_02063a38(void);
extern int func_02023930(void *desc, int a);
extern void *NNS_FndAllocFromDefaultExpHeapEx(unsigned size, int align);
extern int func_02030670(void);
extern int func_ov002_02053558(int id);
extern void func_ov002_02053634(int a, int b, int c, int d, int e, int f, void *cb);
extern int func_ov002_020536bc(int id);
extern void func_ov002_020536dc(int handle, int a);
extern void func_ov002_02053d78(void);
extern void func_ov002_020645b0(void);
extern void func_ov002_02064654(void);
extern void func_ov002_020644dc(void);
extern char *data_ov002_0207f634;
extern int data_ov002_0207edf4;

/* Sets the options page up: clears the state, builds the page, allocates the two 0x20-byte
 * scratch blocks and -- on the debug build -- adds the two extra rows. */
void *func_ov002_020643ac(void) {
    char *page = func_ov002_020636ac();
    char *self = NNSi_FndGetCurrentRootHeap();
    data_ov002_0207f634 = self;
    MI_CpuFill8(self, 0, 0x3c);
    func_ov002_02063a38();
    *(int *)self = func_02023930(&data_ov002_0207edf4, 0);
    *(void **)(self + 8) = NNS_FndAllocFromDefaultExpHeapEx(0x20, 4);
    *(void **)(self + 0xc) = NNS_FndAllocFromDefaultExpHeapEx(0x20, 4);
    *(long long *)(page + 0x18) = 0x6646;
    if (func_02030670() != 0) {
        func_ov002_02053634(func_ov002_02053558(0x3eb), 0, 0x60, 0x10,
                            0x30, 0xffff, (void *)&func_ov002_020645b0);
        func_ov002_02053634(func_ov002_02053558(0x3f9), 0xf0, 0x18, 0x10,
                            0x18, 0xffff, (void *)&func_ov002_02064654);
        func_ov002_020536dc(func_ov002_020536bc(4), 1);
    }
    func_ov002_02053d78();
    return (void *)&func_ov002_020644dc;
}

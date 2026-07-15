/* func_ov008_0204db2c -- main-menu scene constructor, ov008. Grabs the scene heap, brings
 * up the display (func_ov008_0204d7c0) and loads the UI container (func_ov008_0204d8bc),
 * registers the menu message handler, seeds state (selected -1, region flag), and if a
 * pending sub-scene exists, primes it (func_ov008_0204ec34). Returns the top state
 * func_ov008_0204dd24. */
extern void *NNSi_FndGetCurrentRootHeap(void);
extern char *data_ov008_02090f00;
extern void  func_ov008_0204d7c0(void);
extern void  func_ov008_0204d8bc(void);
extern void  func_02030cf8(int, void *);
extern char  func_ov008_0204cd94[];
extern void  func_ov008_0207b84c(int);
extern int   func_02030694(void);
extern int   func_ov008_0204ed3c(void);
extern int   func_ov008_0204cac0(void);
extern void  func_020235bc(int event);
extern int   func_02030788(void);
extern char *func_020315c0(int);
extern void  MI_CpuFill8(void *dst, int val, int size);
extern void  func_ov008_02053a90(void *anchor);
extern char *data_0204be18;
extern int   func_02023588(int);
extern void  func_ov008_0204ec34(void *init);
extern void  func_ov008_0204dd24(void);

void *func_ov008_0204db2c(void) {
    char *heap = (char *)NNSi_FndGetCurrentRootHeap();
    char *sel;
    unsigned char init[6];
    data_ov008_02090f00 = heap;
    func_ov008_0204d7c0();
    func_ov008_0204d8bc();
    func_02030cf8(0xe, func_ov008_0204cd94);
    func_ov008_0207b84c(0);
    *(int *)(heap + 0x14) = -1;
    *(unsigned short *)(heap + 0x504c) = 0xffff;
    *(int *)heap = func_02030694();
    *(unsigned short *)(heap + 0x2c) = 0;
    if (func_ov008_0204ed3c() != 0) {
        *(unsigned short *)(heap + 0x2c) = func_ov008_0204cac0();
    }
    func_020235bc(0x200a);
    func_020235bc(0x200c);
    sel = func_020315c0(func_02030788());
    MI_CpuFill8(init, 0, 6);
    func_ov008_02053a90(data_0204be18 + 0xee0);
    if (sel != 0) {
        init[2] &= ~1;
        *(unsigned short *)(init + 4) = *(int *)(sel + 4);
        init[2] = (init[2] & ~2) | (((unsigned char)func_02023588(0x2010) & 1) << 1);
        init[3] = 0;
        func_ov008_0204ec34(init);
    }
    return (void *)func_ov008_0204dd24;
}

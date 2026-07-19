extern void func_ov005_02058390(void);
extern void func_02034258(int id);
extern void WM_EndKeySharing_0x02023ad0(int h);
extern void MI_CpuFill8(void *dst, int value, unsigned size);
extern int **data_ov005_0205b808;
extern int data_0204c32c;

/* Mission-result teardown: drops the three widgets, forces the capture bit in POWCNT, releases
 * the two node handles and clears the shared result block. */
void func_ov005_020516b4(void) {
    func_ov005_02058390();
    func_02034258(0x15);
    func_02034258(0x1a);
    func_02034258(0x19);
    *(volatile unsigned short *)0x04000304 |= 0x8000;
    WM_EndKeySharing_0x02023ad0(**(int **)&data_ov005_0205b808);
    WM_EndKeySharing_0x02023ad0((*(int **)&data_ov005_0205b808)[1]);
    MI_CpuFill8(&data_0204c32c, 0, 0xac);
}

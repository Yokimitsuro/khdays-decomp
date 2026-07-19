extern char *NNSi_FndGetCurrentRootHeap(void);
extern int func_02020a9c(void);
extern void func_02020888(int engine, void *handler, int a);
extern void func_02023198(void);
extern int *CARDi_GetRomAccessor_0x020315f4(void);
extern void func_02030cf8(int slot, void *handler);
extern void func_020229c4(void);
extern void func_02022d7c(void);
extern void func_02023018(void);
extern void func_02023470(void);
extern void func_02023480(void);
extern void func_0202281c(void);
extern char *data_0204be08;

/* Boots the 3D subsystem: clears the scene block's five counters, installs the three engine
 * handlers unless the language gates them, and arms the two debug hooks. */
void *func_02022708(void) {
    char *self = NNSi_FndGetCurrentRootHeap();
    (&data_0204be08)[1] = self;
    *(int *)((&data_0204be08)[1] + 0xd8) = 0;
    *(int *)((&data_0204be08)[1] + 0xdc) = 0;
    *(int *)((&data_0204be08)[1] + 0xe4) = 0;
    *(int *)((&data_0204be08)[1] + 0xe8) = 0;
    *(int *)((&data_0204be08)[1] + 0xc8) = 0;
    *(int *)((&data_0204be08)[1] + 0xc4) = -1;
    if ((func_02020a9c() & 2) == 0 || (func_02020a9c() & 0x40) == 0) {
        func_02020888(0, (void *)&func_020229c4, 0);
        func_02020888(1, (void *)&func_02022d7c, 0);
        func_02020888(2, (void *)&func_02023018, 0);
    }
    func_02023198();
    if (*CARDi_GetRomAccessor_0x020315f4() != 1) {
        *(unsigned short *)&data_0204be08 = 0;
        func_02030cf8(0x11, (void *)&func_02023470);
        if ((func_02020a9c() & 2) == 0) {
            *(unsigned short *)((char *)&data_0204be08 + 2) = 0;
            func_02030cf8(0x12, (void *)&func_02023480);
        }
    }
    return (void *)&func_0202281c;
}

extern void WM_EndKeySharing_0x0200926c(void);
extern int PXI_IsCallbackReady(int fifoNo, int kind);
extern void PXI_SetFifoRecvCallback(int fifoNo, void (*cb)(int, unsigned int));
extern void OS_InitMutex(void *mutex);
extern void func_0200cbe4(int fifoNo, unsigned int data);

extern struct {
    unsigned short initialized;
    char _2[0xe];
    int field_10;
    char _14[0x8];
    int field_1c;
    int field_20;
} data_020463cc;

extern unsigned short data_02046410[5][4];
extern int data_020463f8;

void func_0200cb40(void)
{
    int i;

    if (data_020463cc.initialized != 0)
        return;

    data_020463cc.initialized = 1;
    data_020463cc.field_1c = 0;
    data_020463cc.field_20 = 0;
    WM_EndKeySharing_0x0200926c();
    while (!PXI_IsCallbackReady(8, 1)) {
    }
    PXI_SetFifoRecvCallback(8, func_0200cbe4);
    for (i = 0; i < 5; i++) {
        data_02046410[i][0] = 0;
    }
    OS_InitMutex(&data_020463f8);
    data_020463cc.field_10 = *(int *)0x027ffc3c;
}

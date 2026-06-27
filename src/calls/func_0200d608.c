extern void WM_EndKeySharing_0x0200926c(void);
extern void PXI_SetFifoRecvCallback(int fifoNo, void (*cb)(int, unsigned int));
extern int PXI_IsCallbackReady(int fifoNo, int kind);
extern void func_0200d720(int fifoNo, unsigned int data);

typedef struct {
    unsigned short initialized;
    char _2[0xa];
    int field_c;
    int field_10;
    int field_14;
    int field_18;
    char _1c[0xc];
    int field_28;
} Data_02046438;

extern Data_02046438 data_02046438;

void func_0200d608(void)
{
    if (data_02046438.initialized != 0)
        return;

    data_02046438.initialized = 1;
    data_02046438.field_c = 0;
    data_02046438.field_10 = 0;
    data_02046438.field_28 = 0;
    data_02046438.field_14 = 0;
    data_02046438.field_18 = 0;
    WM_EndKeySharing_0x0200926c();
    while (!PXI_IsCallbackReady(5, 1)) {
    }
    PXI_SetFifoRecvCallback(5, func_0200d720);
}

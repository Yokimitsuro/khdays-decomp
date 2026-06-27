extern void WM_EndKeySharing_0x0200926c(void);
extern void PXI_SetFifoRecvCallback(int fifoNo, void (*cb)(int, unsigned int));
extern int PXI_IsCallbackReady(int fifoNo, int kind);
extern void func_0200c048(int fifoNo, unsigned int data);

typedef struct {
    unsigned short initialized;
    char _2[0x2];
    int field_4;
    char _8[0x8];
    unsigned short field_10;
    char _12[0x2];
    int field_14;
    char _18[0x1c];
    unsigned short field_34;
    unsigned short field_36;
    unsigned short field_38;
    unsigned short field_3a;
} Data_02046390;

extern Data_02046390 data_02046390;

void func_0200c2c8(void)
{
    if (data_02046390.initialized != 0)
        return;

    data_02046390.initialized = 1;
    WM_EndKeySharing_0x0200926c();
    data_02046390.field_10 = 0;
    data_02046390.field_4 = 0;
    data_02046390.field_14 = 0;
    data_02046390.field_36 = 0;
    data_02046390.field_34 = 0;
    data_02046390.field_3a = 0;
    data_02046390.field_38 = 0;
    while (!PXI_IsCallbackReady(6, 1)) {
    }
    PXI_SetFifoRecvCallback(6, func_0200c048);
}

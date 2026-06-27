extern void WM_EndKeySharing_0x0200926c(void);
extern int PXI_IsCallbackReady(int fifoNo, int kind);
extern void PXI_SetFifoRecvCallback(int fifoNo, void (*cb)(int, unsigned int));
extern void CTRDG_Enable(int enable);
extern void func_0200f3c0(void);
extern void func_0200f78c(void);
extern void func_0200fa30(void *p);
extern void func_0200f980(int fifoNo, unsigned int data);
extern void func_0200f9ac(int fifoNo, unsigned int data);
extern void func_0200fa1c(int fifoNo, unsigned int data);

extern struct {
    char _0[8];
    int initialized;
    int field_c;
    char _10[8];
    int field_18;
} data_02046d50;

extern char data_02046e40;

void func_0200f6d8(void)
{
    if (data_02046d50.initialized != 0)
        return;

    data_02046d50.initialized = 1;
    func_0200f3c0();
    data_02046d50.field_c = 0;
    WM_EndKeySharing_0x0200926c();
    while (!PXI_IsCallbackReady(13, 1)) {
    }
    PXI_SetFifoRecvCallback(13, func_0200f980);
    func_0200f78c();
    PXI_SetFifoRecvCallback(13, 0);
    PXI_SetFifoRecvCallback(13, func_0200f9ac);
    data_02046d50.field_18 = 0;
    func_0200fa30(&data_02046e40);
    PXI_SetFifoRecvCallback(17, func_0200fa1c);
    CTRDG_Enable(0);
}

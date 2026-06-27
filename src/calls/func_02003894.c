extern void WM_EndKeySharing_0x0200926c(void);
extern int PXI_IsCallbackReady(int fifoNo, int kind);
extern void PXI_SetFifoRecvCallback(int fifoNo, void (*cb)(int, unsigned));
extern void func_020038e8(int, unsigned);

extern struct { unsigned short _0; unsigned short state; } data_02044694;

void func_02003894(void)
{
    if (data_02044694.state != 0) return;
    data_02044694.state = 1;
    WM_EndKeySharing_0x0200926c();
    while (!PXI_IsCallbackReady(0xc, 1));
    PXI_SetFifoRecvCallback(0xc, func_020038e8);
}

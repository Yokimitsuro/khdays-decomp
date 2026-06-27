extern void WM_EndKeySharing_0x0200926c();
extern void PXI_SetFifoRecvCallback(int fifoNo, void (*cb)(int, unsigned));
extern void func_0200f220(int, unsigned);
extern int data_02046d40[];

void func_0200f1f4(void) {
    WM_EndKeySharing_0x0200926c();
    PXI_SetFifoRecvCallback(0xe, func_0200f220);
    data_02046d40[1] = 0;
}

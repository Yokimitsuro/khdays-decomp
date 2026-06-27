typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int BOOL;

extern void MI_StopDma(u32 dmaNo);
extern void OS_Terminate(void);
extern void func_0200386c(u32 count);
extern u32  OSi_TryShutdown(void);
extern void CARDi_SendtoPxi(u32 data, u32 wait);

void func_0200f284(void)
{
    BOOL should_be_halt = 1;

    MI_StopDma(0);
    MI_StopDma(1);
    MI_StopDma(2);
    MI_StopDma(3);

    if ((*(volatile u16 *)0x027fffa8 & 0x8000) >> 15) {
        u32 res;
        while ((res = OSi_TryShutdown()) == 4) {
            func_0200386c(0xa3a47);
        }
        if (res == 0) {
            should_be_halt = 0;
        }
    }

    if (should_be_halt) {
        CARDi_SendtoPxi(1, 1);
    }

    OS_Terminate();
}

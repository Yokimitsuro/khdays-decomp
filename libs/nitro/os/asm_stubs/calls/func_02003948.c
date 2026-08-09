extern void OS_Terminate(void);
extern int OS_GetLockID(void);
extern void CARD_LockRom(unsigned short lockId);
extern void MI_StopDma(int channel);
extern void OS_SetIrqMask(unsigned int mask);
extern void OS_ResetRequestIrqMask(unsigned int mask);
extern void OSi_SendToPxi(unsigned int data);
extern void OSi_FinalizeReset(void);

static inline int MB_IsMultiBootChild(void)
{
    return *(volatile unsigned short *)0x027ffc40 == 2;
}

void func_02003948(unsigned int parameter)
{
    unsigned short lockId;

    if (MB_IsMultiBootChild()) {
        OS_Terminate();
    }

    lockId = OS_GetLockID();
    CARD_LockRom(lockId);
    MI_StopDma(0);
    MI_StopDma(1);
    MI_StopDma(2);
    MI_StopDma(3);
    OS_SetIrqMask(0x00040000);
    OS_ResetRequestIrqMask(0xffffffff);
    *(volatile unsigned int *)0x027ffc20 = parameter;
    OSi_SendToPxi(0x10);
    asm {
        ldr r0, =0x027e3f80
        ldr r1, =0x800
        sub r0, r0, r1
        mov sp, r0
        bl OSi_FinalizeReset
    }
}

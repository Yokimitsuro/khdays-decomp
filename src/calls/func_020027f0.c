extern void WM_EndKeySharing_0x0200926c();
extern void OSi_InitVramExclusive();
extern void OS_InitLock();
extern void OSi_InitStackChecker();
extern void func_0200f6d8();
extern void OSi_CancelDma0();
extern void OS_InitIrqTable();
extern void func_02001ba4();
extern void MI_Init();
extern void func_02003894();
extern void func_0200cb40();
extern void func_02002ea4();
extern void OS_InitArenaEx();
extern void CARD_Init();
extern void func_020037a0();
extern void OS_InitArena();

void func_020027f0(void)
{
    OS_InitArena();
    WM_EndKeySharing_0x0200926c();
    OS_InitLock();
    OS_InitArenaEx();
    OS_InitIrqTable();
    OSi_InitStackChecker();
    func_02002ea4();
    MI_Init();
    func_020037a0();
    OSi_InitVramExclusive();
    func_02001ba4();
    func_02003894();
    func_0200f6d8();
    CARD_Init();
    func_0200cb40();
    OSi_CancelDma0();
}

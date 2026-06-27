extern void WM_EndKeySharing_0x0200926c();
extern void OSi_InitVramExclusive();
extern void OS_InitLock();
extern void func_020014b8();
extern void func_0200f6d8();
extern void func_020027d0();
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
    func_020014b8();
    func_02002ea4();
    MI_Init();
    func_020037a0();
    OSi_InitVramExclusive();
    func_02001ba4();
    func_02003894();
    func_0200f6d8();
    CARD_Init();
    func_0200cb40();
    func_020027d0();
}

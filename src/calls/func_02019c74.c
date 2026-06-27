extern void func_0201b094(void);
extern void SND_StopTimer(unsigned chMask, unsigned capMask, unsigned alarmMask, unsigned reserved);
extern unsigned func_020089e8(void);
extern void func_020087c0(int arg);
extern int SND_WaitForCommandProc(unsigned tag);

void func_02019c74(void)
{
    func_0201b094();
    SND_StopTimer(0, 0, 0, 0);
    unsigned tag = func_020089e8();
    func_020087c0(1);
    SND_WaitForCommandProc(tag);
}

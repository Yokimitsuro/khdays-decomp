extern void func_02019f6c(int arg);
extern void func_0201cb80(int arg);
extern void func_0201afac(void);
extern void func_02008458(int arg);
extern void SND_StopTimer(unsigned int chMask, unsigned int capMask, unsigned int alarmMask, unsigned int reserved);
extern unsigned int func_020089e8(void);
extern void func_020087c0(int arg);
extern int SND_WaitForCommandProc(unsigned int tag);

void func_02019c20(void)
{
    func_02019f6c(0);
    func_0201cb80(0);
    func_0201afac();
    func_02008458(0);
    SND_StopTimer(0xffff, 0xffff, 0xffff, 0);
    {
        unsigned int tag = func_020089e8();
        func_020087c0(1);
        SND_WaitForCommandProc(tag);
    }
}

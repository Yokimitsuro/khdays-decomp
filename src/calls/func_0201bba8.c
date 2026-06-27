extern unsigned func_020089e8(void);
extern void func_020087c0(int arg);
extern int SND_WaitForCommandProc(unsigned tag);

void func_0201bba8(void)
{
    unsigned tag = func_020089e8();
    func_020087c0(1);
    SND_WaitForCommandProc(tag);
}

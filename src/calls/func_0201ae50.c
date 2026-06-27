extern void SND_StopTimer(unsigned int chMask, unsigned int capMask, unsigned int alarmMask, unsigned int reserved);
extern unsigned int func_020089e8(void);
extern void func_020087c0(int arg);
extern int SND_WaitForCommandProc(unsigned int tag);

typedef struct {
    char _0[0x24];
    unsigned int flags;
    char _28[0x18];
    unsigned int alarm;
    unsigned int chMask;
} X0201ae50;

void func_0201ae50(X0201ae50 *p)
{
    if (((int)(p->flags << 30) >> 31) == 0)
        return;

    SND_StopTimer(p->chMask, 0, 1 << p->alarm, 0);
    {
        unsigned int tag = func_020089e8();
        func_020087c0(1);
        SND_WaitForCommandProc(tag);
    }
}

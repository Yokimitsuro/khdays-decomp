extern void SND_StopTimer(unsigned int chMask, unsigned int capMask, unsigned int alarmMask, unsigned int reserved);
extern unsigned int func_020089e8(void);
extern void func_020087c0(int arg);
extern int SND_WaitForCommandProc(unsigned int tag);
extern void func_0200d5d8(void *p);
extern void func_0200d5f0(void *p);
extern void func_0201ad60(void *p);

typedef struct {
    char _0[8];
    char _8[0xc];
    char _14[0x10];
    unsigned int flags;
    char _28[0x18];
    unsigned int alarm;
    unsigned int chMask;
} X0201acec;

void func_0201acec(X0201acec *p)
{
    if (((int)(p->flags << 30) >> 31) != 0) {
        SND_StopTimer(p->chMask, 0, 1 << p->alarm, 0);
        func_0200d5d8(&p->_8);
        func_0200d5f0(&p->_14);
        p->flags &= ~2;
        {
            unsigned int tag = func_020089e8();
            func_020087c0(1);
            SND_WaitForCommandProc(tag);
        }
    }
    func_0201ad60(p);
}

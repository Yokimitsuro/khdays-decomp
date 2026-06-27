extern void SND_StartTimer(unsigned int chMask, unsigned int capMask, unsigned int alarmMask, unsigned int flags);
extern void func_0200d5a8(void *p);
extern void func_0200d5c0(void *p);

typedef struct {
    char _0[8];
    char timer0[0xc];
    char timer1[0x10];
    unsigned int flags;
    char _28[0x18];
    unsigned int alarm;
    unsigned int chMask;
} X0201abe0;

void func_0201abe0(X0201abe0 *p)
{
    SND_StartTimer(p->chMask, 0, 1 << p->alarm, 0);

    if (((int)(p->flags << 30) >> 31) != 0)
        return;

    func_0200d5a8(p->timer0);
    func_0200d5c0(p->timer1);
    p->flags |= 2;
}

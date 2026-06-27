extern void SND_StopTimer(unsigned int chMask, unsigned int capMask, unsigned int alarmMask, unsigned int reserved);
extern unsigned int func_020089e8(void);
extern void func_020087c0(int arg);
extern int SND_WaitForCommandProc(unsigned int tag);

typedef struct {
    int active;
    char _4[0x20];
    unsigned int chMask;
    unsigned int capMask;
    int alarm;
} Data_0204acf8;

extern Data_0204acf8 data_0204acf8;

void func_0201b094(void)
{
    Data_0204acf8 *data = &data_0204acf8;
    unsigned int alarmMask;

    if (data->active == 0)
        return;

    if (data->alarm >= 0)
        alarmMask = 1 << data->alarm;
    else
        alarmMask = 0;

    SND_StopTimer(data->chMask, data->capMask, alarmMask, 0);
    {
        unsigned int tag = func_020089e8();
        func_020087c0(1);
        SND_WaitForCommandProc(tag);
    }
}

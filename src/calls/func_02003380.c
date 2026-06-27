extern void OSi_SetTimerReserved(int);
extern void OS_DisableIrqMask(unsigned int);

typedef struct {
    unsigned short active;
    char _2[2];
    void *unk4;
    void *unk8;
} Data_02044674;

extern Data_02044674 data_02044674;

void func_02003380(void)
{
    if (data_02044674.active != 0)
        return;

    data_02044674.active = 1;
    OSi_SetTimerReserved(1);
    data_02044674.unk4 = 0;
    data_02044674.unk8 = 0;
    OS_DisableIrqMask(0x10);
}

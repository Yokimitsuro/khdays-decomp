extern void OSi_SetTimerReserved(unsigned short timer);
extern void OS_SetIrqFunction(unsigned int mask, void (*callback)(void));
extern unsigned int OS_EnableIrqMask(unsigned int mask);
extern void func_0200316c(void);

typedef struct {
    unsigned short active;
    unsigned short _pad;
    int field_4;
    int field_8;
    int field_c;
} Data_02044664;

extern Data_02044664 data_02044664;

#define TM0CNT_L (*(volatile unsigned short *)0x04000100)
#define TM0CNT_H (*(volatile unsigned short *)0x04000102)

void func_020030e4(void)
{
    if (data_02044664.active != 0)
        return;

    data_02044664.active = 1;
    OSi_SetTimerReserved(0);
    data_02044664.field_8 = 0;
    data_02044664.field_c = 0;
    TM0CNT_H = 0;
    TM0CNT_L = 0;
    TM0CNT_H = 0xC1;
    OS_SetIrqFunction(8, func_0200316c);
    OS_EnableIrqMask(8);
    data_02044664.field_4 = 0;
}

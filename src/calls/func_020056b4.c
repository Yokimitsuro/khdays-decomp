#define REG_DISPCNT (*(volatile unsigned int *)0x04000000)
extern unsigned short data_020422b4;
extern unsigned short data_020446d0;

void func_020056b4(unsigned short param_1, unsigned int param_2, int param_3)
{
    int s = data_020422b4;
    unsigned int disp = REG_DISPCNT;

    data_020446d0 = param_1;
    if (s == 0) {
        param_1 = 0;
    }
    REG_DISPCNT = (disp & 0xfff0fff0) | ((unsigned int)param_1 << 16) | param_2 | (param_3 << 3);
    if (data_020446d0 == 0) {
        data_020422b4 = 0;
    }
}

typedef unsigned short u16;
typedef unsigned int u32;

extern void *data_ov009_020563e0;
extern void func_ov009_0204dfcc(int mode);
extern void func_0201e374(int value);
extern void func_0201e3cc(int value);

#define REG_DISPCNT (*(volatile u32 *)0x04000000)
#define REG_DISPCNT_SUB (*(volatile u32 *)0x04001000)
#define REG_POWER_CNT (*(volatile u16 *)0x04000304)

void func_ov009_0204caec(void)
{
    func_ov009_0204dfcc(0);
    func_0201e374(-0x10);
    func_0201e3cc(-0x10);
    REG_DISPCNT &= 0xffffe0ff;
    REG_DISPCNT_SUB &= 0xffffe0ff;
    REG_POWER_CNT |= 0x8000;
    data_ov009_020563e0 = 0;
}

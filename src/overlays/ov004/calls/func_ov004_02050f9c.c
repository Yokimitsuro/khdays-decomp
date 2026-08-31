typedef unsigned long long u64;
typedef struct {
    unsigned char opaque0000[0xaf8];
    int transitionPhase;
    int opaque0afc;
    u64 lastTick;
} Ov004Context;
extern Ov004Context *data_ov004_02051384;
extern u64 func_020031d4(void);
extern void func_0201e374(int brightness);

void func_ov004_02050f9c(void)
{
    u64 elapsed = func_020031d4() - data_ov004_02051384->lastTick;
    func_0201e374(-(int)(elapsed / 0x6646));
    if (elapsed > 0x6646d)
        data_ov004_02051384->transitionPhase = 4;
}

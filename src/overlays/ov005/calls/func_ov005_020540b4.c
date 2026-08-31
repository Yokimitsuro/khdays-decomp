typedef unsigned long long u64;
typedef struct Ov005Context { char opaque00[0x4bf0]; int menuState; u64 startTick; } Ov005Context;
extern Ov005Context *data_ov005_0205b80c;
extern u64 func_020031d4(void);
extern u64 func_02020368(u64,u64);
extern void func_0201e374(int);
#define REG_DISPCNT (*(volatile unsigned int *)0x04000000)
void func_ov005_020540b4(void) {
    u64 elapsed=func_020031d4()-data_ov005_0205b80c->startTick;
    int step=(int)func_02020368(elapsed,0x7fd8);
    if(step>1) {
        REG_DISPCNT=(REG_DISPCNT&~0x1f00)|0x1f00;
        func_0201e374(step-16);
    }
    if(elapsed>0x7fd88) {
        data_ov005_0205b80c->startTick=func_020031d4();
        func_0201e374(0);
        data_ov005_0205b80c->menuState=1;
    }
}

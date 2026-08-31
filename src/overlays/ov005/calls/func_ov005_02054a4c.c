typedef unsigned long long u64;
typedef struct Ov005Context { char opaque00[0x4bf0]; int menuState; u64 startTick; } Ov005Context;
extern Ov005Context *data_ov005_0205b80c;
extern u64 func_020031d4(void);
extern u64 func_02020368(u64,u64);
extern void func_0201e374(int);
extern void func_020336a4(unsigned short);
void func_ov005_02054a4c(void) {
    u64 elapsed=func_020031d4()-data_ov005_0205b80c->startTick;
    func_0201e374(-(int)func_02020368(elapsed,0x7fd8));
    if(elapsed>0x7fd88) {
        func_020336a4(16);
        func_0201e374(-16);
        data_ov005_0205b80c->menuState=8;
    }
}

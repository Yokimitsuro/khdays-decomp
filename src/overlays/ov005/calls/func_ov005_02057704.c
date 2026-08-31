/* Fade out the sub-screen and advance to the finished result phase. */
typedef unsigned long long u64;
typedef struct Ov005ResultContext { char unknown00[0x4b5c]; long long startTick; char unknown4b64[16]; int resultPhase; } Ov005ResultContext;
extern Ov005ResultContext *data_ov005_0205b810;
extern u64 func_020031d4(void), func_02020368(u64, u64);
extern void func_0201e3cc(int);
void func_ov005_02057704(void) {
    u64 elapsed = func_020031d4() - data_ov005_0205b810->startTick;
    func_0201e3cc(-(int)func_02020368(elapsed, 0x7fd8));
    if (elapsed > 0x7fd88) {
        func_0201e3cc(-16);
        data_ov005_0205b810->resultPhase = 4;
    }
}

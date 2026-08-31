/* Fade in the sub-screen and start the first result-count animation. */
typedef unsigned long long u64;
typedef struct Tween { char data[28]; } Tween;
typedef struct Ov005ResultTween { Tween tween; int value; char unknown20[12]; } Ov005ResultTween;
typedef struct Ov005SpriteManager { char data[0x4a80]; } Ov005SpriteManager;
typedef struct Ov005ResultContext {
    char unknown00[0x54];
    Ov005SpriteManager spriteManager;
    char unknown4ad4[0x88];
    long long startTick;
    char unknown4b64[16];
    int resultPhase;
    char unknown4b78[12];
    Ov005ResultTween resultTweens[4];
    int activeTweenIndex;
} Ov005ResultContext;
extern Ov005ResultContext *data_ov005_0205b810;
extern u64 func_020031d4(void), func_02020368(u64, u64);
extern void func_0201e3cc(int), func_ov005_02055bb4(void), func_02035ffc(Tween *);
extern void func_ov005_02055528(int, int);
extern void *func_ov005_0204e0d0(Ov005SpriteManager *, int);
extern void func_ov005_0204e33c(Ov005SpriteManager *, void *);
extern void func_ov005_0204e29c(Ov005SpriteManager *, void *, int);
#define REG_DISPCNT_SUB (*(volatile unsigned int *)0x04001000)
void func_ov005_02057270(void) {
    u64 elapsed = func_020031d4() - data_ov005_0205b810->startTick;
    int step = (int)func_02020368(elapsed, 0x7fd8);
    int tweenIndex, visibleId, releasedId;
    void *entry;
    if (step > 1) {
        REG_DISPCNT_SUB = (REG_DISPCNT_SUB & ~0x1f00) | 0x1f00;
        func_0201e3cc(step - 16);
    }
    if (elapsed <= 0x7fd88) return;
    data_ov005_0205b810->startTick = func_020031d4();
    func_0201e3cc(0);
    data_ov005_0205b810->resultPhase = 1;
    func_ov005_02055bb4();
    tweenIndex = data_ov005_0205b810->activeTweenIndex;
    func_02035ffc(&data_ov005_0205b810->resultTweens[tweenIndex].tween);
    switch (tweenIndex) {
    case 1: releasedId = 32; visibleId = 31; break;
    case 2: releasedId = 47; visibleId = 46; break;
    case 3: releasedId = 62; visibleId = 61; break;
    default: return;
    }
    func_ov005_02055528(releasedId, 0);
    entry = func_ov005_0204e0d0(&data_ov005_0205b810->spriteManager, releasedId);
    func_ov005_0204e33c(&data_ov005_0205b810->spriteManager, entry);
    entry = func_ov005_0204e0d0(&data_ov005_0205b810->spriteManager, visibleId);
    func_ov005_0204e29c(&data_ov005_0205b810->spriteManager, entry, 1);
}

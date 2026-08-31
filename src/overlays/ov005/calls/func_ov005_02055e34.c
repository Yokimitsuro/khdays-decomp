/* Update reward sprite sequences and multiplier indicators as counters finish. */
typedef unsigned char u8;
typedef unsigned int u32;
typedef struct TweenFlags { u32 started:1, paused:1, finished:1, reserved:29; } TweenFlags;
typedef struct Tween { char unknown00[24]; TweenFlags flags; } Tween;
typedef struct Ov005ResultTween { Tween tween; int duration, currentValue, fromValue, toValue; } Ov005ResultTween;
typedef struct Ov005GaugeRange { int maximum, value; } Ov005GaugeRange;
typedef struct Ov005SpriteManager { char data[0x4a80]; } Ov005SpriteManager;
typedef struct Ov005ResultContext {
    char unknown00[0x54];
    Ov005SpriteManager spriteManager;
    char unknown4ad4[0xb0];
    Ov005ResultTween resultTweens[4];
    char unknown4c34[20];
    u8 modeSnapshot, unknown4c49[3];
    Ov005GaugeRange gauge, previousGauge;
} Ov005ResultContext;
typedef struct Ov005Config { char unknown00[0x4c]; u32 rewardScales[3]; char unknown58[4]; u8 mode; } Ov005Config;
extern Ov005ResultContext *data_ov005_0205b810;
extern Ov005Config data_ov005_0205b85c;
extern void func_02033b78(int, int);
extern void func_ov005_02055528(int, u32);
extern void func_ov005_02055d2c(u32, int);
extern void *func_ov005_0204e0d0(Ov005SpriteManager *, int);
extern void func_ov005_0204e300(Ov005SpriteManager *, void *);
extern u32 func_ov005_0204e14c(Ov005SpriteManager *, void *);
extern u32 func_ov005_0204e378(Ov005SpriteManager *, void *);
void func_ov005_02055e34(void) {
    u8 index;
    int entryId;
    int hasMultiplier;
    Ov005Config *config = &data_ov005_0205b85c;
    Ov005ResultContext *context = data_ov005_0205b810;
    u8 *modeSnapshot = &context->modeSnapshot;
    int maximum = context->gauge.maximum;
    int previousMaximum = context->previousGauge.maximum;
    if (previousMaximum < maximum || (previousMaximum > 0 && maximum == 0)) {
        ++*modeSnapshot;
        func_02033b78(0, 58);
        if (data_ov005_0205b810->resultTweens[3].tween.flags.finished) *modeSnapshot = config->mode;
    }
    hasMultiplier = 0;
    for (index = 0; index < 3; index++) {
        if (config->rewardScales[index] != 0x1000) { hasMultiplier = 1; break; }
    }
    for (index = 0; index < 3; index++) {
        Ov005ResultTween *entry = &data_ov005_0205b810->resultTweens[index + 1];
        switch (index + 1) {
        case 1: entryId = 32; break;
        case 2: entryId = 47; break;
        case 3: entryId = 62; break;
        }
        if (entry->tween.flags.finished) {
            if (!hasMultiplier) func_ov005_02055528(entryId, 2);
            else { func_ov005_02055528(entryId, 0); func_ov005_02055d2c(index, 1); }
            func_ov005_0204e300(&data_ov005_0205b810->spriteManager,
                func_ov005_0204e0d0(&data_ov005_0205b810->spriteManager, entryId));
        } else if (hasMultiplier) {
            if (func_ov005_0204e14c(&data_ov005_0205b810->spriteManager,
                func_ov005_0204e0d0(&data_ov005_0205b810->spriteManager, entryId))) {
                if (!func_ov005_0204e378(&data_ov005_0205b810->spriteManager,
                    func_ov005_0204e0d0(&data_ov005_0205b810->spriteManager, entryId))) func_ov005_02055d2c(index, 1);
                else func_ov005_02055d2c(index, 0);
            }
        }
    }
}

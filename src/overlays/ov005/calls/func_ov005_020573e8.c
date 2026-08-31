/* Advance result counters, honor completion requests, and update the result display. */
typedef unsigned char u8;
typedef struct Tween { char data[28]; } Tween;
typedef struct Ov005ResultTween { Tween tween; int duration, currentValue, fromValue, toValue; } Ov005ResultTween;
typedef struct Ov005SpriteManager { char data[0x4a80]; } Ov005SpriteManager;
typedef struct Ov005ResultContext {
    char unknown00[0x54];
    Ov005SpriteManager spriteManager;
    char unknown4ad4[0xa0];
    int resultPhase;
    char unknown4b78[12];
    Ov005ResultTween resultTweens[4];
    int activeTweenIndex;
    char unknown4c38[16];
    u8 modeSnapshot;
    char unknown4c49[19];
    int finishAllCounters, finishActiveCounters;
} Ov005ResultContext;
typedef struct Ov005Config {
    char unknown00[12];
    unsigned short rewardMode;
    char unknown0e[30];
    int updateMissionRecord;
    char unknown30[44];
    u8 bMode;
    char unknown5d[7];
    int nOption64;
} Ov005Config;
extern Ov005ResultContext *data_ov005_0205b810;
extern Ov005Config data_ov005_0205b85c;
extern void func_ov005_02056078(void), func_ov005_02056010(void), func_ov005_020557a8(void);
extern void func_ov005_020563b0(void), func_ov005_02055e34(void), func_ov005_020558c0(void);
extern int func_ov005_02055c4c(void);
extern void func_02035ffc(Tween *), func_ov005_02055528(int, unsigned int);
extern void func_02033bb4(int, int, int), func_02033b78(int, int);
extern void *func_ov005_0204e0d0(Ov005SpriteManager *, int);
extern void func_ov005_0204e29c(Ov005SpriteManager *, void *, int);
extern void func_ov005_0204e33c(Ov005SpriteManager *, void *);
static inline void ShowEntry(int id) {
    void *entry = func_ov005_0204e0d0(&data_ov005_0205b810->spriteManager, id);
    func_ov005_0204e29c(&data_ov005_0205b810->spriteManager, entry, 1);
}
void func_ov005_020573e8(void) {
    Ov005Config *config = &data_ov005_0205b85c;
    int busy, tweenIndex, visibleId, releasedId;
    void *entry;
    if (data_ov005_0205b810->resultTweens[data_ov005_0205b810->activeTweenIndex].toValue == 0)
        data_ov005_0205b810->finishActiveCounters = 1;
    if (data_ov005_0205b810->finishActiveCounters) {
        func_ov005_02056078();
        data_ov005_0205b810->finishActiveCounters = 0;
    }
    if (data_ov005_0205b810->finishAllCounters) {
        func_ov005_02056010();
        if (config->nOption64 == 0 && config->rewardMode != 255 && config->rewardMode != 8)
            func_ov005_020557a8();
        if (config->updateMissionRecord) ShowEntry(config->rewardMode == 2 ? 109 : 110);
        data_ov005_0205b810->resultPhase = 2;
        func_02033bb4(0, 52, 0);
        data_ov005_0205b810->modeSnapshot = config->bMode;
        func_ov005_020563b0();
        ShowEntry(31);
        ShowEntry(46);
        ShowEntry(61);
    }
    busy = func_ov005_02055c4c();
    func_ov005_02055e34();
    func_ov005_020558c0();
    if (busy) return;
    if (data_ov005_0205b810->finishAllCounters) return;
    data_ov005_0205b810->activeTweenIndex++;
    tweenIndex = data_ov005_0205b810->activeTweenIndex;
    if (tweenIndex < 4) {
        func_02035ffc(&data_ov005_0205b810->resultTweens[tweenIndex].tween);
        switch (tweenIndex) {
        case 1: releasedId = 32; visibleId = 31; break;
        case 2: releasedId = 47; visibleId = 46; break;
        case 3: releasedId = 62; visibleId = 61; break;
        default: goto sound_check;
        }
        func_ov005_02055528(releasedId, 0);
        entry = func_ov005_0204e0d0(&data_ov005_0205b810->spriteManager, releasedId);
        func_ov005_0204e33c(&data_ov005_0205b810->spriteManager, entry);
        ShowEntry(visibleId);
sound_check:
        if (data_ov005_0205b810->activeTweenIndex == 1) func_02033b78(0, 52);
    } else data_ov005_0205b810->finishAllCounters = 1;
}

/* Configure the four result counters, converting their endpoints to 20.12 values. */
typedef unsigned char u8;
typedef struct Tween { char data[28]; } Tween;
typedef struct Ov005ResultTween { Tween tween; int duration, unknown20, fromValue, toValue; } Ov005ResultTween;
typedef struct Ov005ResultContext { char unknown00[0x4b84]; Ov005ResultTween resultTweens[4]; } Ov005ResultContext;
typedef struct Ov005Config {
    char unknown00[12];
    unsigned short rewardMode;
    char unknown0e[26];
    int missionResultValue;
    char unknown2c[8];
    int rewardBase0c, rewardBase08, rewardBase04;
} Ov005Config;
extern Ov005Config data_ov005_0205b85c;
extern Ov005ResultContext *data_ov005_0205b810;
extern void func_02035fb0(Tween *, int, int, int, int);
void func_ov005_02055bb4(void) {
    u8 index;
    Ov005ResultTween *tweens = data_ov005_0205b810->resultTweens;
    Ov005Config *config = &data_ov005_0205b85c;
    tweens[0].toValue = config->missionResultValue;
    tweens[1].toValue = config->rewardBase0c;
    tweens[2].toValue = config->rewardBase08;
    tweens[3].toValue = config->rewardBase04;
    for (index = 0; index < 4; index++) {
        Ov005ResultTween *entry = &tweens[index];
        int target = entry->toValue;
        if (index != 0 || config->rewardMode != 0) target <<= 12;
        func_02035fb0(&entry->tween, 0, entry->fromValue << 12, target, entry->duration);
    }
}

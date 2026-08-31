/* Render the three base rewards and the resulting scaled totals. */
typedef unsigned char u8;
typedef unsigned int u32;
typedef struct Ov005ResultTween { char tween[28]; int duration, currentValue, fromValue, toValue; } Ov005ResultTween;
typedef struct Ov005ResultContext { char unknown00[0x4b84]; Ov005ResultTween resultTweens[4]; } Ov005ResultContext;
typedef struct Ov005Config { char unknown00[0x34]; int rewardBases[3], rewardTotals[3]; u32 rewardScales[3]; } Ov005Config;
extern Ov005ResultContext *data_ov005_0205b810;
extern Ov005Config data_ov005_0205b85c;
extern int func_ov005_020578c4(int), func_ov005_02057b40(int, u32);
extern void func_ov005_02055480(u32, int, int, int);
void func_ov005_02055688(void) {
    int values[3] = {
        (u32)data_ov005_0205b810->resultTweens[1].currentValue > 999999 ? 999999 : data_ov005_0205b810->resultTweens[1].currentValue,
        (u32)data_ov005_0205b810->resultTweens[2].currentValue > 999999 ? 999999 : data_ov005_0205b810->resultTweens[2].currentValue,
        data_ov005_0205b810->resultTweens[3].currentValue
    };
    int baseEntryIds[3];
    int totalEntryIds[3];
    u8 index;
    int value;
    Ov005Config *config = &data_ov005_0205b85c;
    baseEntryIds[0] = 33; baseEntryIds[1] = 48; baseEntryIds[2] = 63;
    totalEntryIds[0] = 39; totalEntryIds[1] = 54; totalEntryIds[2] = 69;
    for (index = 0; index < 3; index++) {
        u8 digitCount = func_ov005_020578c4(config->rewardBases[index]);
        value = values[index];
        func_ov005_02055480(value, baseEntryIds[index], digitCount, 0);
        value = config->rewardTotals[index] + func_ov005_02057b40(value, config->rewardScales[index]);
        if (value > 999999) value = 999999;
        digitCount = func_ov005_020578c4(value);
        func_ov005_02055480(value, totalEntryIds[index], digitCount, 0);
    }
}

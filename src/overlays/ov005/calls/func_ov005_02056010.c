/* Start all result tweens and remove both durations so sampling completes them. */
#pragma opt_common_subs off
typedef struct Tween { int mode, duration; char unknown08[20]; } Tween;
typedef struct Ov005ResultTween { Tween tween; int duration, currentValue, fromValue, toValue; } Ov005ResultTween;
typedef struct Ov005ResultContext { char unknown00[0x4b84]; Ov005ResultTween resultTweens[4]; } Ov005ResultContext;
extern Ov005ResultContext *data_ov005_0205b810;
extern void func_02035ffc(Tween *);
void func_ov005_02056010(void) {
    unsigned char index;
    for (index = 0; index < 4; index++) {
        func_02035ffc(&data_ov005_0205b810->resultTweens[index].tween);
        data_ov005_0205b810->resultTweens[index].tween.duration = 0;
        data_ov005_0205b810->resultTweens[index].duration = 0;
    }
}

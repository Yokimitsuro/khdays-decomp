/* Zero both durations of each result counter that has started. */
typedef struct TweenFlags { unsigned int started:1, paused:1, finished:1, reserved:29; } TweenFlags;
typedef struct Tween { int mode, duration; char unknown08[16]; TweenFlags flags; } Tween;
typedef struct Ov005ResultTween { Tween tween; int duration, currentValue, fromValue, toValue; } Ov005ResultTween;
typedef struct Ov005ResultContext { char unknown00[0x4b84]; Ov005ResultTween resultTweens[4]; } Ov005ResultContext;
extern Ov005ResultContext *data_ov005_0205b810;
void func_ov005_02056078(void) {
    unsigned char index;
    Ov005ResultTween *tweens = data_ov005_0205b810->resultTweens;
    for (index = 0; index < 4; index++) {
        if (tweens[index].tween.flags.started) {
            data_ov005_0205b810->resultTweens[index].tween.duration = 0;
            data_ov005_0205b810->resultTweens[index].duration = 0;
        }
    }
}

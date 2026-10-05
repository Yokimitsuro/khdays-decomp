/* Steps the row scale tweens and, when the header tween ends, records the time and moves to the
 * dwell timer. */

#include "nitro/types.h"

typedef struct Ov022TweenFlags {
    u32 unknown0 : 2;
    u32 finished : 1;
    u32 unknown3 : 29;
} Ov022TweenFlags;

typedef struct Ov022Tween {
    int values[6];
    Ov022TweenFlags flags;
} Ov022Tween;

typedef struct Ov022Row {
    char padding000[0x10];
    volatile int tweenValueA;
    volatile int tweenValueB;
    int scaleA;
    int scaleB;
    char padding020[0x10];
} Ov022Row;

typedef struct Ov022Pair {
    int a;
    int b;
} Ov022Pair;

typedef struct Ov022RootContext {
    Ov022Row rows[4];
    signed char state;
    signed char substate1;
    signed char substate2;
    signed char substate3;
    int timestamp;
    Ov022Tween tweenHeader;
    Ov022Tween tweenFooter;
    Ov022Tween rowTweenA[4];
    Ov022Tween rowTweenB[4];
} Ov022RootContext;

extern Ov022RootContext *NNSi_FndGetCurrentRootHeap(void);
extern void Tween_Sample(Ov022Tween *tween, int *value);
extern long long OS_GetTick(void);
extern unsigned long long func_02020368(unsigned long long dividend, unsigned long long divisor);
extern int FX_Mul(int a, int b);
extern void func_ov022_02086e80(int count);
extern int Ov022_WaitDwellTimer(void);
extern int data_0204be04;

int Ov022_StepScaleTweens(void)
{
    Ov022RootContext *context = NNSi_FndGetCurrentRootHeap();
    int result = 0;
    int value;
    Ov022Pair tweenValue;
    Ov022Pair scale;
    volatile Ov022Pair tweenCopy;
    volatile Ov022Pair scaleCopy;
    int scaleBValue;

    if (*(unsigned char *)&data_0204be04 != 0) {
        return result;
    }

    Tween_Sample(&context->tweenHeader, &value);
    if (context->tweenHeader.flags.finished) {
        context->timestamp = (int)func_02020368(OS_GetTick() << 6, 0x82ea);
        result = (int)Ov022_WaitDwellTimer;
    }

    *(volatile int *)&scale.a = FX_Mul(0x1000, value);
    scaleBValue = FX_Mul(0x1000, value);
    scaleCopy.a = scaleBValue;
    scale.b = scaleBValue;
    {
        Ov022Row *row = context->rows;
        int i;
        Ov022Tween *rowTweenA = context->rowTweenA;
        Ov022Tween *rowTweenB = context->rowTweenB;

        scaleCopy.b = scale.a;
        i = 0;
        do {
            int tweenA;
            int tweenB;

            row->scaleA = scaleCopy.b;
            row->scaleB = scaleCopy.a;
            Tween_Sample(rowTweenA, &tweenValue.b);
            Tween_Sample(rowTweenB, &tweenValue.a);
            tweenA = tweenValue.b;
            tweenB = tweenValue.a;
            row->tweenValueA = tweenA;
            row->tweenValueB = tweenB;
            tweenCopy.a = tweenA;
            tweenCopy.b = tweenB;
            i++;
            row++;
            rowTweenA++;
            rowTweenB++;
        } while (i < 4);
    }
    func_ov022_02086e80(4);
    return result;
}

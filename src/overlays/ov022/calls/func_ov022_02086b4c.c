typedef unsigned int u32;

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
extern void func_0203602c(Ov022Tween *tween, int *value);
extern long long func_020031d4(void);
extern unsigned long long func_02020368(long long value, int divisor, int flag);
extern int func_02005418(int a, int b);
extern void func_ov022_02086e80(int count);
extern int func_ov022_02086c10(void);
extern int data_0204be04;

int func_ov022_02086b4c(void)
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

    func_0203602c(&context->tweenHeader, &value);
    if (context->tweenHeader.flags.finished) {
        context->timestamp = (int)func_02020368(func_020031d4() << 6,
                                               0x82ea, 0);
        result = (int)func_ov022_02086c10;
    }

    *(volatile int *)&scale.a = func_02005418(0x1000, value);
    scaleBValue = func_02005418(0x1000, value);
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
            func_0203602c(rowTweenA, &tweenValue.b);
            func_0203602c(rowTweenB, &tweenValue.a);
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

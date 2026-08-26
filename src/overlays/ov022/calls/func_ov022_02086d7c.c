typedef struct Ov022Pair {
    int a;
    int b;
} Ov022Pair;

typedef struct Ov022SavedPair {
    int a;
    int b;
} Ov022SavedPair;

typedef struct Ov022ScaleSourcePair {
    unsigned int a;
    unsigned int b;
} Ov022ScaleSourcePair;

typedef struct Ov022Preset {
    Ov022Pair target[4];
    Ov022Pair initial;
} Ov022Preset;

typedef struct Ov022PresetTable {
    Ov022Preset presets[5];
} Ov022PresetTable;

typedef struct Ov022RowFlags {
    unsigned char lowFlags : 5;
    unsigned char highFlags : 3;
} Ov022RowFlags;

typedef struct Ov022Row {
    char padding000[0x10];
    int valueA;
    int valueB;
    Ov022ScaleSourcePair scale;
    char padding020[4];
    unsigned char marker;
    char padding025[5];
    Ov022RowFlags flags;
    char padding02b[5];
} Ov022Row;

typedef struct Ov022Tween {
    int values[7];
} Ov022Tween;

typedef struct Ov022RootContext {
    Ov022Row rows[4];
    char padding0c0[8];
    Ov022Tween tweenHeader;
    Ov022Tween tweenFooter;
    Ov022Tween rowTweenA[4];
    Ov022Tween rowTweenB[4];
} Ov022RootContext;

extern Ov022RootContext *const data_ov022_020b2e74;
extern const Ov022PresetTable data_ov022_020b22a4;
extern const Ov022ScaleSourcePair data_ov022_020b229c;
extern int func_02024e5c(void);
extern void func_02035fb0(Ov022Tween *tween, int mode, int start, int target,
                          int duration);
extern void func_02035ffc(Ov022Tween *tween);

void func_ov022_02086d7c(void)
{
    unsigned int scaleB __attribute__((aligned(8)));
    unsigned int scaleA;
    int rowB;
    int rowA;
    int variant;
    Ov022PresetTable table;
    Ov022ScaleSourcePair scaleSource;
    Ov022RootContext *context;
    int i;
    int startA;
    volatile Ov022SavedPair savedInitial;
    Ov022Row *row;
    volatile unsigned int *startValues;
    Ov022Tween *tweenA;
    Ov022Tween *tweenB;
    int startB;

    context = data_ov022_020b2e74;
    table = data_ov022_020b22a4;
    scaleSource = data_ov022_020b229c;
    variant = func_02024e5c();
    if (variant > 0) {
        variant--;
    }
    i = 0;
    {
    int targetOffset = variant * 40;
    int *tableBase = (int *)&table;
    int *target;
    row = context->rows;
    target = (int *)((char *)tableBase + targetOffset);
    tweenA = context->rowTweenA;
    tweenB = context->rowTweenB;
    rowA = target[8];
    rowB = target[9];
    savedInitial.a = rowA;
    savedInitial.b = rowB;
    startValues = (volatile unsigned int *)target;
    startA = startValues[8];
    startB = startValues[9];
    scaleA = scaleSource.a;
    scaleB = scaleSource.b;
    do {
        row->valueA = rowA;
        row->valueB = rowB;
        row->scale.a = scaleA;
        row->scale.b = scaleB;
        row->flags.lowFlags = 0x1f;
        row->marker = 0x3e;
        func_02035fb0(tweenA, 2, startA, target[0], 200);
        func_02035ffc(tweenA);
        func_02035fb0(tweenB, 2, startB, target[1], 200);
        func_02035ffc(tweenB);
        row++;
        target += 2;
        tweenA++;
        tweenB++;
        i++;
    } while (i < 4);
    }
    func_02035fb0(&context->tweenHeader, 2, 0, 0x1000, 200);
    func_02035ffc(&context->tweenHeader);
}

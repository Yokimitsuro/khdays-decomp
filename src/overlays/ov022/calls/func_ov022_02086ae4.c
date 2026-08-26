typedef unsigned int u32;

typedef struct Ov022RootFlags {
    u32 unknown0 : 2;
    u32 finished : 1;
    u32 unknown3 : 29;
} Ov022RootFlags;

typedef struct Ov022RootContext {
    char padding000[0xc0];
    signed char state;
    signed char substate1;
    signed char substate2;
    signed char substate3;
    char padding0c4[0x11c];
    int tweenCursor[6];
    Ov022RootFlags flags;
} Ov022RootContext;

extern Ov022RootContext *NNSi_FndGetCurrentRootHeap(void);
extern void func_0203602c(void *tween, int *value);
extern void func_ov022_02086d7c(void);
extern void func_02033b24(int a, int b);
extern void func_ov022_02086d60(int value);
extern int func_ov022_02086970(void);
extern int func_ov022_02086b4c(void);
extern int data_0204be04;

int func_ov022_02086ae4(void)
{
    Ov022RootContext *context = NNSi_FndGetCurrentRootHeap();
    int value;
    int result = 0;

    if (*(unsigned char *)&data_0204be04 != 0) {
        return 0;
    }

    func_0203602c(context->tweenCursor, &value);
    if (context->flags.finished) {
        if (context->substate3 == 0) {
            context->state = 0;
            result = (int)func_ov022_02086970;
        } else {
            func_ov022_02086d7c();
            func_02033b24(0, 0x27);
            value = 0;
            result = (int)func_ov022_02086b4c;
        }
    }
    func_ov022_02086d60(value);
    return result;
}

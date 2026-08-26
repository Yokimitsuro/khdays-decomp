typedef struct Ov022Tween {
    int values[7];
} Ov022Tween;

typedef struct Ov022RootContext {
    char padding000[0xc4];
    int timestamp;
    Ov022Tween tweenHeader;
    Ov022Tween tweenFooter;
} Ov022RootContext;

extern Ov022RootContext *NNSi_FndGetCurrentRootHeap(void);
extern long long func_020031d4(void);
extern unsigned long long func_02020368(long long value, int divisor, int flag);
extern void func_02035fb0(Ov022Tween *tween, int mode, int start, int target,
                          int duration);
extern void func_02035ffc(Ov022Tween *tween);
extern void func_ov022_02086e80(int count);
extern int func_ov022_02086c9c(void);
extern int data_0204be04;

int func_ov022_02086c10(void)
{
    Ov022RootContext *context = NNSi_FndGetCurrentRootHeap();
    int result = 0;
    unsigned long long now;
    int limit;

    if (*(unsigned char *)&data_0204be04 != 0) {
        return 0;
    }

    now = func_02020368(func_020031d4() << 6, 0x82ea, 0);
    limit = context->timestamp + 800;
    if (now > (unsigned long long)(long long)limit) {
        func_02035fb0(&context->tweenHeader, 2, 0x1000, 0x3000, 200);
        func_02035ffc(&context->tweenHeader);
        func_02035fb0(&context->tweenFooter, 2, 0x1000, 0, 200);
        func_02035ffc(&context->tweenFooter);
        result = (int)func_ov022_02086c9c;
    }
    func_ov022_02086e80(4);
    return result;
}

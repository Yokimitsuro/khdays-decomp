typedef signed char s8;
typedef short s16;
typedef unsigned short u16;

typedef int (*Ov022StateCallback)(void);

typedef struct Ov022InitArgs {
    s16 kind;
    s16 x;
    s16 y;
    char pad_0006[0x82];
    void *externalObject;
} Ov022InitArgs;

typedef struct Ov022Context {
    u16 flags;
    char pad_0002[6];
    void *slots[3];
    void *childObjects[2];
    int viewX;
    int viewY;
    char pad_0024[8];
    void *externalObject;
    int value;
    int scale;
    u16 x;
    u16 y;
    s8 kind;
    s8 phase;
    s8 state;
} Ov022Context;

extern Ov022Context *data_ov022_020b2e60;
extern void *data_ov022_020b2880[2];

extern Ov022Context *NNSi_FndGetCurrentRootHeap(void);
extern void func_ov022_02083178(void);
extern void *func_02023930(void *classDescriptor, int argument);
extern int func_ov002_0206d9b8(void);
extern void *func_ov022_02083f40(void);
extern void func_ov002_0204cc9c(void *owner, int value, int unused);
extern unsigned char func_0202c440(void);
extern int func_02023c40(void);
extern void func_ov002_0206d69c(void);
extern void func_ov002_02076868(int value);
extern void func_ov002_02076534(void);
extern int func_ov022_02082bf4(void);

Ov022StateCallback func_ov022_02082acc(Ov022InitArgs *args)
{
    Ov022Context *context;
    unsigned int i;
    int value;

    context = NNSi_FndGetCurrentRootHeap();
    data_ov022_020b2e60 = context;
    context->viewX = (int)0xffff0000;
    context->viewY = (int)0xffff0000;
    context->kind = (s8)args->kind;
    context->externalObject = args->externalObject;
    context->x = args->x;
    context->y = args->y;
    context->phase = -1;
    context->value = 0;
    func_ov022_02083178();

    for (i = 0; i < 2; i++) {
        context->childObjects[i] = func_02023930(data_ov022_020b2880[i], 1);
    }

    value = func_ov002_0206d9b8();
    if (value >= 0) {
        func_ov002_0204cc9c(func_ov022_02083f40(), value, 0);
    }
    func_0202c440();
    context->flags = 0x16;
    context->scale = func_02023c40() == 1 ? 0x1800 : 0x1000;
    context->state = -1;
    func_ov002_0206d69c();
    func_ov002_02076868(context->scale);
    func_ov002_02076534();
    return func_ov022_02082bf4;
}

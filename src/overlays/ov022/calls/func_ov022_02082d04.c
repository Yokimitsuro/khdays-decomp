typedef signed char s8;
typedef unsigned short u16;

typedef void *(*Ov022StateCallback)(void);

typedef struct Ov022Context {
    u16 flags;
    char pad_0002[0x3b];
    s8 phase;
    s8 state;
} Ov022Context;

typedef struct GameRuntimeContext {
    void *activeObject;
    char pad_0004[0x38];
    int pendingValue;
} GameRuntimeContext;

extern Ov022Context *data_ov022_020b2e60;

extern void func_ov002_02072034(void);
extern GameRuntimeContext *OS_IsThreadAvailable_0x020c9848(void);
extern void func_ov002_02074054(int enabled);
extern int func_02023588(unsigned int flagId);
extern void func_ov002_02077eb4(void);
extern void func_02020878(char value);
extern void *func_ov022_02082d8c(void);

Ov022StateCallback func_ov022_02082d04(void)
{
    Ov022Context *context = data_ov022_020b2e60;

    if ((context->flags & 4) != 0) {
        context->flags &= ~4;
    } else {
        context->state = 2;
    }

    func_ov002_02072034();
    context->flags &= ~0x10;

    if (OS_IsThreadAvailable_0x020c9848() != 0 &&
        OS_IsThreadAvailable_0x020c9848()->activeObject != 0) {
        func_ov002_02074054(1);
        if (func_02023588(0x20b5) != 0) {
            GameRuntimeContext *runtime = OS_IsThreadAvailable_0x020c9848();
            if (runtime != 0) {
                runtime->pendingValue = 0;
            }
        }
    }

    func_ov002_02077eb4();
    if ((context->flags & 0x100) != 0) {
        func_02020878(1);
        context->flags &= ~0x100;
    }

    return func_ov022_02082d8c;
}

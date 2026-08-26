typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long long u64;

typedef void *(*Ov022StateCallback)(void);

typedef struct Ov022Context {
    u16 flags;
    char pad_0002[0x22];
    u64 startedAt;
    char pad_002c[8];
    int duration;
} Ov022Context;

typedef struct GameRuntimeContext {
    char pad_0000[0x3c];
    int pendingValue;
} GameRuntimeContext;

extern u8 data_0204c240;
extern Ov022Context *data_ov022_020b2e60;

extern int func_02023c40(void);
extern void func_ov002_0206b9e4(int id, int slot, int payload);
extern u64 func_020031d4(void);
extern void func_ov022_02088830(void);
extern int func_ov022_02083f0c(void);
extern void func_ov002_0204cee0(int object, int enabled);
extern GameRuntimeContext *OS_IsThreadAvailable_0x020c9848(void);
extern void func_020336a4(int event);
extern void func_020340d0(int enabled);
extern void func_020235e8(int field, int width, int value);

extern void *func_ov022_02083aac(void);
extern void *func_ov022_02083844(void);

Ov022StateCallback func_ov022_02083038(void)
{
    Ov022Context *context = data_ov022_020b2e60;

    if ((data_0204c240 & 4) == 0) {
        GameRuntimeContext *runtime;
        int duration;

        context->flags |= 0x10;
        context->duration = func_02023c40() == 1 ? 0xf0 : 0xa0;
        func_ov002_0206b9e4(-2, -3, 0);
        context->startedAt = func_020031d4();
        func_ov022_02088830();
        func_ov002_0204cee0(func_ov022_02083f0c(), 1);

        duration = func_02023c40() == 1 ? 0xf0 : 0xa0;
        runtime = OS_IsThreadAvailable_0x020c9848();
        if (runtime != 0) {
            runtime->pendingValue = duration;
        }

        func_020336a4(0x78);
        func_020340d0(1);
        func_020235e8(0x20e6, 1, 1);
        return func_ov022_02083aac;
    }

    context->flags |= 0x10;
    return func_ov022_02083844;
}

typedef signed int s32;
typedef unsigned int u32;
typedef unsigned long long u64;
typedef unsigned char u8;

typedef void (*Ov022Callback)(void);

typedef struct Ov022ControllerFlags {
    unsigned int bit0 : 1;
    unsigned int bit1 : 1;
    unsigned int scheduleEnabled : 1;
    unsigned int rest : 29;
} Ov022ControllerFlags;

typedef struct Ov022SelectionController {
    u8 pad000[0xc4];
    s32 scheduledHandle0c4;
    u8 pad0c8[0x118];
    u8 tween1e0[0x18];
    Ov022ControllerFlags flags1f8;
} Ov022SelectionController;

extern u8 data_0204be04;
extern Ov022SelectionController *NNSi_FndGetCurrentRootHeap(void);
extern void func_0203602c(void *tween, s32 *value);
extern void func_ov022_02086d0c(int enabled);
extern u64 func_020031d4(void);
extern s32 func_02020368(u64 value, u32 divisor, int mode);
extern void func_ov022_02086d60(s32 value);
extern void func_ov022_02086a90(void);

Ov022Callback func_ov022_02086a24(void)
{
    Ov022SelectionController *context = NNSi_FndGetCurrentRootHeap();
    Ov022Callback callback = 0;
    s32 value;

    if (data_0204be04 != 0) {
        return callback;
    }

    func_0203602c(context->tween1e0, &value);
    if (context->flags1f8.scheduleEnabled != 0) {
        func_ov022_02086d0c(0);
        value = 0x10000;
        context->scheduledHandle0c4 =
            func_02020368(func_020031d4() << 6, 0x82ea, 0);
        callback = func_ov022_02086a90;
    }

    func_ov022_02086d60(value);
    return callback;
}

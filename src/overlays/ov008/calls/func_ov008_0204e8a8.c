typedef unsigned char u8;
typedef unsigned int u32;

typedef union Ov008FlagsByte {
    u8 raw;
    struct {
        u8 bit0 : 1;
        u8 synchronized : 1;
        u8 rest : 6;
    } bits;
} Ov008FlagsByte;

typedef struct Ov008PlayerFlags {
    Ov008FlagsByte flags;
    u8 pad_0001[5];
} Ov008PlayerFlags;

typedef struct Ov008MenuContext {
    u8 pad_0000[0x30];
    Ov008PlayerFlags playerFlags[4];
    Ov008FlagsByte sharedFlags;
} Ov008MenuContext;

extern Ov008MenuContext *data_ov008_02090f00;

extern void func_ov008_0204d564(void);
extern int func_ov008_0207baf8(void);
extern u32 func_02030788(void);
extern void func_ov008_0204d6a8(int slot);
extern void func_020307b8(int enabled);
extern void func_ov008_0204e04c(void);

void *func_ov008_0204e8a8(void)
{
    if (func_ov008_0204d564(), func_ov008_0207baf8() != 0) {
        u32 slot = func_02030788();
        Ov008MenuContext *context = data_ov008_02090f00;

        context->playerFlags[slot].flags.bits.synchronized =
            context->sharedFlags.bits.synchronized;
    }

    {
        Ov008MenuContext *context = data_ov008_02090f00;
        u32 slot = func_02030788();

        if (context->playerFlags[slot].flags.bits.synchronized !=
            context->sharedFlags.bits.synchronized) {
            return 0;
        }
    }

    func_ov008_0204d6a8((int)func_02030788());
    func_020307b8(0);
    return (void *)func_ov008_0204e04c;
}

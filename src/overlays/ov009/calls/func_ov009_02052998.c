typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Ov009SaveSlot {
    u16 profileValue;
    u16 cellCount;
    int gameValue8;
    int field40a;
    int gameValue0;
    int mappedResult;
    int hasCompleteData;
    int fieldC4b;
} Ov009SaveSlot;

typedef struct Ov009SaveContext {
    int variant;
    u8 pad004[0x04];
    int state;
    int result;
    u8 pad010[0x04];
    Ov009SaveSlot slots[3];
    u8 pad068[0x1d4];
    int transferState;
    u8 pad240[0x1cbc];
    u32 sequence;
    u8 flag18bd;
    u8 flag18c9;
} Ov009SaveContext;

extern int func_020235d0(int field, int kind);
extern void func_020235e8(int field, int kind, u16 value);
extern int func_02023e80(u16 range);
extern int func_02023588(int flag);
extern void func_020235bc(int flag);
extern int func_ov009_02055e18(int slot);

int func_ov009_02052998(Ov009SaveContext *ctx, int slot)
{
    u32 sequence;
    int result;

    func_020235e8(0x452, 9, (u16)func_020235d0(0, 9));

    ctx->slots[slot].fieldC4b =
        func_02023e80(
            (u16)((u32)func_020235d0(0, 9) >= 0x1a ? 3 : 2));
    func_020235e8(0xc4b, 2, (u16)ctx->slots[slot].fieldC4b);
    func_020235e8(0xc98, 2, (u16)slot);

    sequence = ctx->sequence + 1;
    func_020235e8(0xc77, 0x10, (u16)(sequence >> 16));
    func_020235e8(0xc87, 0x10, (u16)sequence);

    ctx->flag18bd = func_02023588(0x18bd);
    ctx->flag18c9 = func_02023588(0x18c9);
    func_020235bc(0x18bd);
    func_020235bc(0x18c9);

    result = func_ov009_02055e18(slot);
    ctx->transferState = 3;
    return result;
}

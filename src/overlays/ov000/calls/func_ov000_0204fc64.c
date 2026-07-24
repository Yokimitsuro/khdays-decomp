/* func_ov000_0204fc64 -- Scene 1: tick one load-phase slot (Ghidra: Ov000_UpdateLoadState).
 * State machine on context->loadState (+0x4afb): state 0 arms the slot (current = base,
 * stride 0x20 at +0x4b20), calls the phase starter and advances to state 1; state 1 polls
 * func_ov000_0204f6e0 -- 3 = save-check special path (state 2, mode 3, control word at
 * +0x6a48 = (x & 0xffff0000) | 1, both counters cleared), >= 0 = record the result
 * (func_ov000_0204faf0(slot, result)) and optionally set bit0 of +0x6a50 when
 * GameState field 0x44e reads 6. Returns the (possibly updated) state byte.
 * MATCH NOTES: func_ov000_0204f7ac really takes the slot argument (its own file matched
 * as void(void) because a dropped trailing arg does not change the callee's bytes), and
 * func_ov000_0204faf0 takes (slot, result) -- result homed in r1 produces the ROM's
 * mov r1,r0 after the poll call. Return type is u8 (caller func_ov000_02051d3c). */
typedef unsigned char  u8;
typedef unsigned int   u32;

typedef struct Ov000PageSlot {
    int base;
    int current;
    u8  pad_0008[0x18];
} Ov000PageSlot;

typedef struct Ov000LoadContext {
    u8 pad_0000[0x4adc];
    int field_4adc;
    u8 pad_4ae0[0x4afb - 0x4ae0];
    u8 loadState;
    u8 pad_4afc[0x4b20 - 0x4afc];
    Ov000PageSlot slots[1];
} Ov000LoadContext;

typedef struct Ov000FadeBlock {
    u8 pad_0000[0x6a48];
    u32 controlWord;
    u8 pad_6a4c[4];
    u32 resultWord;
    u32 requestWord;
    u8 pad_6a58[4];
    u32 counterA;
    u32 counterB;
} Ov000FadeBlock;

extern Ov000LoadContext *data_ov000_0205ac24;

extern void func_ov000_0204f7ac(int slot);
extern int  func_ov000_0204f6e0(void);
extern void func_ov000_0204faf0(int slot, int result);
extern int  func_020235d0(int a, int b);

u8 func_ov000_0204fc64(int slot)
{
    Ov000LoadContext *ctx = data_ov000_0205ac24;

    switch (ctx->loadState) {
    case 0:
        ctx->slots[slot].current = ctx->slots[slot].base;
        func_ov000_0204f7ac(slot);
        data_ov000_0205ac24->loadState = 1;
        break;
    case 1: {
        int result;
        result = func_ov000_0204f6e0();
        if (result == 3) {
            data_ov000_0205ac24->loadState = 2;
            data_ov000_0205ac24->field_4adc = 3;
            ((Ov000FadeBlock *)data_ov000_0205ac24)->controlWord =
                (((Ov000FadeBlock *)data_ov000_0205ac24)->controlWord & 0xffff0000) | 1;
            ((Ov000FadeBlock *)data_ov000_0205ac24)->counterA = 0;
            ((Ov000FadeBlock *)data_ov000_0205ac24)->counterB = 0;
        } else if (result >= 0) {
            func_ov000_0204faf0(slot, result);
            data_ov000_0205ac24->loadState = 2;
            if (((Ov000FadeBlock *)data_ov000_0205ac24)->requestWord != 0) {
                if (func_020235d0(0x44e, 3) == 6) {
                    ((Ov000FadeBlock *)data_ov000_0205ac24)->resultWord |= 1;
                }
            }
        }
        break;
    }
    }
    return data_ov000_0205ac24->loadState;
}

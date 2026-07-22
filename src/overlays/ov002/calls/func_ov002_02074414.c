/* Claim the pending slot for `seat`, taking the kind out of byte 1 of the source
 * object's word at +0x2d0. A slot that is already claimed (non-negative) is left
 * alone. Always reports 0. */
typedef struct {
    char pad0000[0x96];
    signed char bSeat;      /* +0x96, negative = unclaimed */
    unsigned char bKind;    /* +0x97 */
} Ov002SlotContext;

extern Ov002SlotContext *data_ov002_0207fa14;

int func_ov002_02074414(int seat, char *source) {
    Ov002SlotContext *ctx = data_ov002_0207fa14;

    if (ctx->bSeat >= 0) {
        return 0;
    }

    {
        unsigned char kind = (unsigned char)(*(unsigned int *)(source + 0x2d0) >> 8);
        ctx->bSeat = (signed char)seat;
        ctx->bKind = kind;
    }
    return 0;
}

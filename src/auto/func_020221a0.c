struct Outer;
typedef int (*CallbackFunc)(struct Outer *ctx, int arg);

typedef struct CallbackEntry {
    CallbackFunc func;
    int arg;
} CallbackEntry;

typedef struct Slot {
    unsigned char unk00[0x1c];
    CallbackEntry *current;
    CallbackEntry callbacks[5];
} Slot; /* size 0x48 */

typedef struct Outer {
    unsigned char unk000[0x124];
    int currentIndex;
} Outer;

int func_020221a0(Outer *ctx, int *pValue)
{
    Slot *slot = (Slot *)((unsigned char *)ctx + 4 + ctx->currentIndex * 0x48);
    int idx = *pValue - 1;
    int result = 1;

    if (slot->callbacks[idx].func != 0) {
        result = slot->callbacks[idx].func(ctx, slot->callbacks[idx].arg);
        if (result == 0) {
            slot->current = &slot->callbacks[idx];
        } else {
            slot->callbacks[idx].func = 0;
            slot->callbacks[idx].arg = 0;
        }
    }

    return result;
}

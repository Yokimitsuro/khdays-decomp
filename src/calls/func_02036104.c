typedef unsigned int u32;
typedef unsigned long long u64;

/* A stopwatch over the 64-bit tick counter: while it is running, nTick holds
   the tick it was started at; while it is held, nTick holds the span that has
   accumulated so far. Both directions are the same subtraction. */
typedef struct {
    u32 field_00;
    u32 field_04;
    u32 field_08;
    u32 field_0c;
    u64 nTick;              /* 0x10 */
    u32 field_18_bit0 : 1;  /* 0x18 */
    u32 bHeld : 1;
    u32 field_18_rest : 30;
} Stopwatch;

extern u64 func_020031d4(void);

void func_02036104(Stopwatch *pWatch, int bHold)
{
    if (bHold != 0) {
        if (pWatch->bHeld != 0) {
            return;
        }
        pWatch->bHeld = 1;
        pWatch->nTick = func_020031d4() - pWatch->nTick;
    } else {
        if (pWatch->bHeld == 0) {
            return;
        }
        pWatch->bHeld = 0;
        pWatch->nTick = func_020031d4() - pWatch->nTick;
    }
}

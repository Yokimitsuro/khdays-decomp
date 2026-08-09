extern int OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(int state);
extern int OsCountZeroBits(unsigned int value);
extern int data_02044698;
extern unsigned short data_0204469c;

/* Releases every VRAM bank of `mask` that this owner holds, clearing both the per-bank owner table
 * and the global in-use mask. */
void OSi_UnlockVram(unsigned int mask, unsigned short owner) {
    unsigned int mine;
    int enabled = OS_DisableInterrupts();
    int bit;
    unsigned int clear;
    mine = mask & data_02044698 & 0x1ff;
    for (;;) {
        bit = 0x1f - OsCountZeroBits(mine);
        if (bit < 0) {
            break;
        }
        clear = ~(1 << bit);
        mine &= clear;
        if (owner == (&data_0204469c)[bit]) {
            (&data_0204469c)[bit] = 0;
            data_02044698 &= clear;
        }
    }
    OS_RestoreInterrupts(enabled);
}

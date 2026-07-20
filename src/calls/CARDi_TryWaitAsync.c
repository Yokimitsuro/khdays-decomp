/* CARDi_TryWaitAsync: returns 1 if the card context's busy bit (+0x114, bit 2) is clear. */

extern int data_020464e0;

int CARDi_TryWaitAsync(void) {
    return (*(int *)((int)&data_020464e0 + 0x114) & 4) == 0;
}

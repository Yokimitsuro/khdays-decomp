/* Tiny veneer: tail-call resetBankForX_(&data_020446e6).
 * `ldr ip,[pc,#4] ; ldr r0,[pc,#4] ; bx ip` -- a void tail call to a far/interworking target.
 * One of 87 byte-identical veneers differing only in the two pooled symbols.
 *
 * The SDK name is misattributed: all 87 are called SNDi_UnlockMutex_0xADDR while tail-calling 5
 * different targets. The identifier matched a SHAPE, not a function. Trust the bytes. */
extern void resetBankForX_(void *p);
extern int data_020446e6;

void SNDi_UnlockMutex_0x020063e4(void) {
    resetBankForX_(&data_020446e6);
}

/* Tiny veneer: tail-call disableBankForX_(&data_020446d4).
 * `ldr ip,[pc,#4] ; ldr r0,[pc,#4] ; bx ip` -- a void tail call to a far/interworking target.
 * One of 87 byte-identical veneers differing only in the two pooled symbols.
 *
 * The SDK name is misattributed: all 87 are called SNDi_UnlockMutex_0xADDR while tail-calling 5
 * different targets. The identifier matched a SHAPE, not a function. Trust the bytes. */
extern void disableBankForX_(void *p);
extern int data_020446d4;

void SNDi_UnlockMutex_0x020065d4(void) {
    disableBankForX_(&data_020446d4);
}

/* Tiny veneer: tail-call OS_LockMutex(&data_02044730).
 * `ldr ip,[pc,#4] ; ldr r0,[pc,#4] ; bx ip` -- a void tail call to a far/interworking target.
 * One of 87 byte-identical veneers differing only in the two pooled symbols.
 *
 * The SDK name is misattributed: all 87 are called SNDi_UnlockMutex_0xADDR while tail-calling 5
 * different targets. The identifier matched a SHAPE, not a function. Trust the bytes. */
extern void OS_LockMutex(void *p);
extern int data_02044730;

void SNDi_UnlockMutex_0x020084f4(void) {
    OS_LockMutex(&data_02044730);
}

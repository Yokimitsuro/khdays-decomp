/* Tiny cross-overlay veneer: tail-call srand_0x0208875c(&func_ov090_020bcaf8).
 * `ldr ip,[pc] ; ldr r0,[pc] ; bx ip` -- mwcc emits this for a void tail call to a far/interworking
 * target (families.md's veneer vein). One of 87 byte-identical veneers differing only in the two
 * pooled symbols.
 *
 * NOTE: the symbol name is almost certainly misattributed. This is called SNDi_UnlockMutex_ov090_0x020ba7c0 but tail-calls
 * srand_0x0208875c -- an SDK mutex helper would not. Do not trust the name; the bytes are what match. */
extern void srand_0x0208875c(void *p);
extern int func_ov090_020bcaf8;

void SNDi_UnlockMutex_ov090_0x020ba7c0(void) {
    srand_0x0208875c(&func_ov090_020bcaf8);
}

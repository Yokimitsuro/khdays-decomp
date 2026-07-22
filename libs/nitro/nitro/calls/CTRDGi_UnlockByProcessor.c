/* Releases the cartridge (only while the nesting counter at +0 is zero) and always
 * restores the interrupt state saved at +4.
 *
 * The processor id is forwarded to OS_UnLockCartridge; that is what keeps r0 live and
 * pushes the nesting-counter load into r1 as the ROM does. */
extern void OS_UnLockCartridge();
extern void OS_RestoreInterrupts(int state);

void CTRDGi_UnlockByProcessor(int id, int *ctx) {
    if (ctx[0] == 0) {
        OS_UnLockCartridge(id);
    }
    OS_RestoreInterrupts(ctx[1]);
}

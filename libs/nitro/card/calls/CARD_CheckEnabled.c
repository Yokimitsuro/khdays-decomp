/* Aborts the system when the card thread is not available. */
extern int OS_IsThreadAvailable_0x0200e068(void);
extern void OS_Terminate(void);

void CARD_CheckEnabled(void) {
    if (OS_IsThreadAvailable_0x0200e068() == 0) {
        OS_Terminate();
    }
}

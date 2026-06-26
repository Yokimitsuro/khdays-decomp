extern int OS_IsThreadAvailable_0x0200e068();
extern int OS_Terminate();

void CARD_CheckEnabled(void) {
    if (OS_IsThreadAvailable_0x0200e068() == 0) {
        OS_Terminate();
    }
}

/* Releases the card bus and then the ROM resource lock. */
extern void OS_UnlockCard_0x0200179c(int id);
extern void CARDi_UnlockResource(int id, int resource);

void CARD_UnlockRom(int id) {
    OS_UnlockCard_0x0200179c(id);
    CARDi_UnlockResource(id, 1);
}

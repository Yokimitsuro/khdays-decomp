/* Releases the cartridge lock word and frees the bus through the shared helper. */
extern void *OSi_DoUnlockByWord();
extern void OSi_FreeCartridgeBus(void);

void *OS_TryLockCartridge(int id) {
    return OSi_DoUnlockByWord(id, (void *)0x27fffe8, OSi_FreeCartridgeBus, 1);
}

/* Takes the cartridge lock word and allocates the bus through the shared helper. */
extern void *OSi_DoTryLockByWord();
extern void OSi_AllocateCartridgeBus(void);

void *OS_TryLockCartridge_0x02001730(int id) {
    return OSi_DoTryLockByWord(id, (void *)0x27fffe8, OSi_AllocateCartridgeBus, 1);
}

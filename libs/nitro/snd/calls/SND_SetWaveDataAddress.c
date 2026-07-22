/* Publishes one wave-data pointer to the ARM7 under the sound mutex. */
extern void SNDi_UnlockMutex_0x020084f4(void);
extern void SNDi_UnlockMutex_0x02008508(void);
extern void DC_StoreRange(void *p, unsigned int len);

void SND_SetWaveDataAddress(char *table, int slot, void *addr) {
    SNDi_UnlockMutex_0x020084f4();
    *(void **)(table + slot * 4 + 0x3c) = addr;
    DC_StoreRange(table + 0x3c + slot * 4, 4);
    SNDi_UnlockMutex_0x02008508();
}

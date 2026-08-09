extern int OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(int state);

extern int CTRDG_IsOptionCartridge(void);
extern void OS_SetDPermissionsForProtectionRegion(int region, int perms);
extern int data_02046d48;

/* Opens or closes the cartridge bus, adjusting the MPU permissions for its region. */
void CTRDG_Enable(int enable) {
    int enabled = OS_DisableInterrupts();
    int perms;
    data_02046d48 = enable;
    if (CTRDG_IsOptionCartridge() == 0) {
        if (enable != 0) {
            perms = 0x1000;
        } else {
            perms = 0x5000;
        }
        OS_SetDPermissionsForProtectionRegion(0xf000, perms);
    }
    OS_RestoreInterrupts(enabled);
}

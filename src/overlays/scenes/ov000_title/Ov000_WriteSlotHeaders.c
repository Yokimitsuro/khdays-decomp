#include "game/engine.h"

extern void CARD_LockBackup(int lock);
extern int Ov000_EmitCommandAndStoreHandle(int a, int *out, int b);
extern void MI_CpuFill8(void *dst, int value, unsigned size);
extern int Ov000_BackupWrite(int off, void *buf, unsigned size);
extern void CARD_UnlockBackup(int lock);
extern void OS_WaitVBlankIntr(void);
extern unsigned short data_0204be10;
extern void *data_0204be14;

/* Writes both copies of one save slot's header. Returns 0 if the card refuses at any point. */
int Ov000_WriteSlotHeaders(int slot) {
    int scratch;
    Sleep_Block();
    CARD_LockBackup(data_0204be10);
    if (Ov000_EmitCommandAndStoreHandle(0, &scratch, 1) == 0) {
        MI_CpuFill8(data_0204be14, 0, 0x2018);
        slot *= 2;
        if (Ov000_BackupWrite(slot * 0x2018 + 0x20, data_0204be14, 0x20) == 0) {
            CARD_UnlockBackup(data_0204be10);
            OS_WaitVBlankIntr();
            CARD_LockBackup(data_0204be10);
            if (Ov000_BackupWrite((slot + 1) * 0x2018 + 0x20, data_0204be14, 0x20) == 0) {
                CARD_UnlockBackup(data_0204be10);
                Sleep_Unblock();
                return 1;
            }
        }
    }
    CARD_UnlockBackup(data_0204be10);
    Sleep_Unblock();
    return 0;
}

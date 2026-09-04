typedef unsigned short u16;
typedef unsigned int u32;

extern void *OS_UnlockByWord(int id, void *word, void *callback);
extern void *OS_UnlockByWord_0x02001688(int id, void *word, void *callback);
extern void WaitByLoop(u32 count);
extern void INITi_CpuClear32_0x01ff86fc(u32 value, void *destination, u32 size);

/* The once-only guard: every call after the first returns immediately. */
extern u32 data_02044308;

/* The lock word the two processors share, at the top of the main-RAM window.
   The ARM7 clears `extension` once it has handed the buses over. */
typedef struct {
    u32 lockFlag;
    u16 ownerId;
    u16 extension;
} OSLockWord;

extern OSLockWord data_027ffff0;

/* The lock-id allocation bitmap: two words of reserved ids, then the owner table. */
#define OSi_LockIdFlags  ((u32 *)0x027fffb0)

#define REG_EXMEM_CNT    (*(volatile u16 *)0x04000204)

#define OS_LOCKID_INIT   0x7e
#define OS_LOCKID_ERROR  0x7f

/* Bring the inter-processor lock system up, once.
 *
 * Takes the init lock, waits for the ARM7 to release the buses, resets the lock-id
 * bitmap so the low ids are free, hands the card slot (EXMEMCNT bit 11) and the
 * cartridge slot (bit 7) to the ARM7, then releases the init lock and claims the
 * error id.
 */
void OS_InitLock(void)
{
    if (data_02044308 != 0) {
        return;
    }
    data_02044308 = 1;
    data_027ffff0.lockFlag = 0;
    OS_UnlockByWord(OS_LOCKID_INIT, &data_027ffff0, 0);

    {
        OSLockWord *w = &data_027ffff0;

        while (w->extension != 0) {
            WaitByLoop(0x400);
        }
    }

    OSi_LockIdFlags[0] = 0xffffffff;
    OSi_LockIdFlags[1] = 0xffff0000;
    INITi_CpuClear32_0x01ff86fc(0, OSi_LockIdFlags + 4, 40);

    REG_EXMEM_CNT |= 0x800;
    REG_EXMEM_CNT |= 0x80;

    OS_UnlockByWord_0x02001688(OS_LOCKID_INIT, &data_027ffff0, 0);
    OS_UnlockByWord(OS_LOCKID_ERROR, &data_027ffff0, 0);
}

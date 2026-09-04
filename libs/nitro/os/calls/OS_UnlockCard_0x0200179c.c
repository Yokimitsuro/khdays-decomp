typedef unsigned short u16;

typedef struct OSLockWord {
    u16 lockFlag;
    u16 extension;
} OSLockWord;

typedef void (*OSLockCallback)(void);

extern void OS_UnlockByWord_0x02001688(u16 lockId, OSLockWord *lock, OSLockCallback onFree);
extern void OSi_FreeCardBus(void);

/* The card lock word lives at a fixed address in the shared region, so its
   address is a plain literal rather than a relocated symbol. */
#define OSi_CardLock ((OSLockWord *)0x027fffe0)

/* Despite the inherited symbol name this is the lock-side entry: it installs the
   bus release callback, where the unlock-side wrapper installs the allocate one. */
void OS_UnlockCard_0x0200179c(u16 lockId)
{
    OS_UnlockByWord_0x02001688(lockId, OSi_CardLock, OSi_FreeCardBus);
}

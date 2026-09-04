typedef unsigned short u16;

typedef struct OSLockWord {
    u16 lockFlag;
    u16 extension;
} OSLockWord;

typedef void (*OSLockCallback)(void);

extern void OS_UnlockByWord(u16 lockId, OSLockWord *lock, OSLockCallback onFree);
extern void OSi_AllocateCardBus(void);

/* The card lock word lives at a fixed address in the shared region, so its
   address is a plain literal rather than a relocated symbol. */
#define OSi_CardLock ((OSLockWord *)0x027fffe0)

void OS_UnlockCard(u16 lockId)
{
    OS_UnlockByWord(lockId, OSi_CardLock, OSi_AllocateCardBus);
}

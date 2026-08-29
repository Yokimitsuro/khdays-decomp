typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;

typedef struct Ov002DayEntry {
    u8 nEntry;              /* 0x00 */
    u8 bDay;                /* 0x01, replaces the name's day when bit 15 is up */
    char pad002[1];
    s8 nExtra;              /* 0x03 */
    u16 hFlags;             /* 0x04 */
} Ov002DayEntry;

/* What the session publishes about the day currently being played.  Every
   player's record is pointed at this one copy. */
typedef struct Ov002DayNotice {
    u8 bValid;              /* 0x00 */
    u8 bDay;                /* 0x01 */
    u8 nEntry;              /* 0x02 */
    s8 nExtra;              /* 0x03 */
} Ov002DayNotice;

typedef struct Ov002CodeBase {
    char pad000[0x0e];
    u8 bFlags;              /* 0x0e, bit 1 means the notice is still stale */
    char pad00f[0x20];
    s8 aSlots[4];           /* 0x2f */
    char pad033[0xcd];
    Ov002DayNotice notice;  /* 0x100 */
} Ov002CodeBase;

extern Ov002CodeBase *data_ov002_0207fa10;

extern Ov002DayEntry *func_ov002_02071420(int nDay, int nSlotValue);
/* Index of the local player; zero for the one running the session. */
extern int func_02030788(void);
extern void func_ov002_0206b084(void);
/* Number of players the session currently holds. */
extern int func_ov022_020882f8(void);
extern char *func_01fffde0(int nPlayer);
extern int func_01fffe14(void);

/* Publish the day one slot is playing.
 *
 * The slot's own value picks the day entry, and the parts of it the rest of
 * the game reads are copied into the session's single notice, which is only
 * marked valid once it is filled.  The player running the session points every
 * player's record at that notice; anyone else only points their own.
 */
void func_ov002_0207220c(int nSlot, int nDay)
{
    Ov002CodeBase *pBase;
    Ov002DayEntry *pEntry;
    int i;

    pBase = data_ov002_0207fa10;
    pEntry = func_ov002_02071420(nDay, pBase->aSlots[nSlot]);
    if (func_02030788() != 0) {
        func_ov002_0206b084();
    }

    pBase->notice.bDay = pEntry->bDay;
    pBase->notice.nEntry = pEntry->nEntry;
    pBase->notice.nExtra = pEntry->nExtra;
    pBase->notice.bValid = 1;

    if (func_02030788() == 0) {
        for (i = 0; i < func_ov022_020882f8(); i++) {
            *(Ov002DayNotice **)(func_01fffde0(i) + 0x2668) = &pBase->notice;
        }
    } else {
        *(Ov002DayNotice **)(func_01fffde0(func_01fffe14()) + 0x2668) =
            &pBase->notice;
    }

    pBase->bFlags &= ~2;
}

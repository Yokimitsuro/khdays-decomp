typedef unsigned char u8;
typedef signed char s8;

typedef struct Vec3 {
    int x;
    int y;
    int z;
} Vec3;

extern char *data_ov002_0207fa10;
extern u8 data_0204c240;                /* g_modeAndDayClock; bit 2 gates this */

extern int func_ov002_0206b758(void);           /* is the tally live */
extern int func_01fffe14(void);                 /* the local peer */
extern int func_ov022_02088474(int nPeer);      /* peer -> kind, or negative */

/* Copies out where each of the local peer's link items sits and returns how
 * many there were.
 *
 * Only the boot mode that raises bit 2 has them, and only while the tally is
 * live.  The context keeps eight item slots per kind and a signed count per
 * kind alongside them; the count is re-read every pass, so an item that goes
 * away mid-copy shortens the walk.  A peer with no kind, or a kind with no
 * items, copies nothing and answers zero.
 */
int func_ov002_020729cc(Vec3 *aOut)
{
    char *pCtx;
    s8 *pCount;
    char *pKind;
    int nKind;
    int i;
    char *pSlot;

    pCtx = data_ov002_0207fa10;
    if ((data_0204c240 & 4) != 0 && func_ov002_0206b758() != 0) {
        nKind = func_ov022_02088474(func_01fffe14());
        if (nKind >= 0) {
            pCount = (s8 *)(pCtx + 0xfc + nKind);
            i = 0;
            if (*(s8 *)(pCtx + 0xfc + nKind) > 0) {
                pSlot = pCtx + nKind * 0x20;
                pKind = pCtx + nKind;
                do {
                    *aOut = *(Vec3 *)(*(char **)(pSlot + 0x7c) + 8);
                    i++;
                    pSlot += 4;
                    aOut++;
                } while (i < *(s8 *)(pKind + 0xfc));
            }
            return *pCount;
        }
    }
    return 0;
}

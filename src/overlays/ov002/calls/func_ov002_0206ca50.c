typedef unsigned char u8;
typedef signed char s8;

extern char *data_ov002_0207fa00;
extern u8 data_0204c248[];              /* [1] gates showing ranks at all */

extern void MI_CpuFill8(void *pDst, int nValue, int nSize);
extern int func_ov002_0206b758(void);           /* Ov002_IsSessionOpen */
extern int func_ov022_020882f8(void);           /* how many seats are in */
extern int func_02023588(int nFlag);

/* Ranks the seats that are in by their figure and writes one rank byte each
 * into aRank, which is four bytes long.
 *
 * All four start at 0xff and stay there unless a session is open, more than one
 * seat is in, and the gating byte allows it.  Game flag 0x20dc short-circuits
 * the whole thing: it answers true with the 0xff fill left in place, so the
 * caller shows no ranks rather than showing everyone tied.
 *
 * A seat whose figure is zero is stamped 3, last.  Every other seat counts how
 * many seats strictly outscore it, so the best gets 0 and seats that tie share
 * a rank.  The seat count is re-read from ov022 on every pass of both loops
 * rather than held in a local, which is what the ROM does.
 *
 * The roster rows are Ov002SeatRow, 0x2c apart, and the figure is +0x24.
 * Called from Ov002_StepPanelScreen. */
int func_ov002_0206ca50(s8 *aRank)
{
    char *pRoot;
    char *pBase;
    int j;
    int i;
    char *pSeat;
    char *pOtherSeat;

    pRoot = data_ov002_0207fa00;
    pBase = pRoot + 0x8bcc;
    MI_CpuFill8(aRank, 0xff, 4);

    if (func_ov002_0206b758() != 0 && func_ov022_020882f8() > 1
        && data_0204c248[1] != 0) {
        if (func_02023588(0x20dc) != 0) {
            return 1;
        }

        i = 0;
        if (func_ov022_020882f8() > 0) {
            pSeat = pBase;
            do {
                if (*(int *)(pSeat + 0x24) == 0) {
                    aRank[i] = 3;
                } else {
                    j = 0;
                    aRank[i] = 0;
                    if (func_ov022_020882f8() > 0) {
                        pOtherSeat = pBase;
                        do {
                            j++;
                            if (*(int *)(pSeat + 0x24) < *(int *)(pOtherSeat + 0x24)) {
                                aRank[i] = (s8)(aRank[i] + 1);
                            }
                            pOtherSeat += 0x2c;
                        } while (j < func_ov022_020882f8());
                    }
                }
                i++;
                pSeat += 0x2c;
            } while (i < func_ov022_020882f8());
        }
        return 1;
    }
    return 0;
}

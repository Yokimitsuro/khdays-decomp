/* func_ov008_0205ff4c -- Ov008_FindPanelCardOfKind: scan the three-bank card grid
 * (+0x19c4, 3 banks of 0x28 slots, 0xa0 apart) for a card in state 5 or 6 whose
 * kind (+0x22) is nKind.  On a hit, cache the tier record for that state (0x1f for
 * state 6, 0x20 for state 5) at +0x2078 and answer 1; otherwise 0.  Sibling of
 * 0205ffe8: same walk, same split displacement, same i/j/base declaration order.
 */
typedef struct Ov008PanelCard {
    char pad_00[0x18];
    int  nState;              /* 0x18 */
    char pad_1c[6];
    short nKind;              /* 0x22 */
} Ov008PanelCard;

#define CARD_STATE_A 5
#define CARD_STATE_B 6
#define TIER_STATE_B 0x1f
#define TIER_STATE_A 0x20

extern void *func_ov008_02055c84(void *pRecords, int nTier);   /* GetVarRecordByIndex */

int func_ov008_0205ff4c(int self, int nKind)
{
    int i;
    int j;
    char *base;

    i = 0;
    base = (char *)self;
    do {
        j = 0;
        do {
            Ov008PanelCard *pCard = ((Ov008PanelCard **)(base + 0x19c4))[j];
            if (pCard != 0 && pCard->nState - CARD_STATE_A <= 1u && pCard->nKind == nKind) {
                if (pCard->nState == CARD_STATE_B) {
                    *(void **)(self + 0x2078) = func_ov008_02055c84((void *)(self + 0x28c), TIER_STATE_B);
                } else {
                    *(void **)(self + 0x2078) = func_ov008_02055c84((void *)(self + 0x28c), TIER_STATE_A);
                }
                return 1;
            }
            j++;
        } while (j < 0x28);
        i++;
        base += 0xa0;
    } while (i < 3);
    return 0;
}

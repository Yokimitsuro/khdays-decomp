/* func_ov026_0208df80 -- Ov008_CountSpareItemsOfChild: how many copies of the child
 * entry's item the party still has unequipped -- its stock minus one per equipped
 * slot (three members, forty slots each) that holds it.  Nothing when the child has
 * no item.
 */
typedef unsigned char  u8;
typedef unsigned short u16;

#define MEMBER_COUNT 3
#define SLOT_COUNT   40

typedef struct GameState {
    u8  pad_0000[0x810];
    u8  aItemCount[0x6d0];            /* 0x810 */
    u16 aEquipped[MEMBER_COUNT][SLOT_COUNT]; /* 0xee0 */
} GameState;

extern GameState *data_0204be18;
extern int func_ov026_0208df6c(int nChild);   /* GetChildField14OrNeg1 */

u8 func_ov026_0208df80(int nChild)
{
    int nItem;
    u8 nSpare;
    int nMember;
    int nSlot;
    GameState *pState;

    nItem = func_ov026_0208df6c(nChild);
    if (nItem < 0) {
        return 0;
    }
    pState = data_0204be18;
    nSpare = pState->aItemCount[nItem];
    for (nMember = 0; nMember < MEMBER_COUNT; nMember++) {
        for (nSlot = 0; nSlot < SLOT_COUNT; nSlot++) {
            if (nItem == pState->aEquipped[nMember][nSlot] && nSpare != 0) {
                nSpare--;
            }
        }
    }
    return nSpare;
}
